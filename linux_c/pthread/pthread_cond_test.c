/*
* @Author: llseng
* @Date:   2020-06-29 14:49:14
* @Last Modified by:   llseng
* @Last Modified time: 2020-07-01 17:45:18
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

static pthread_mutex_t mutex; //PTHREAD_MUTEX_INITIALIZER; //互斥锁初始化常量(结构体常量)
static pthread_cond_t cond; //PTHREAD_COND_INITIALIZER; //条件变量初始化常量(结构体常量)

static pthread_t tid_1;
static pthread_t tid_2;

//链表
struct node {
    int value;
    struct node *next;
};
static struct node* head = NULL;

//生产者
static void *producer( void *param ) {
    int count = 0;
    struct node *lnode;

    pthread_detach( pthread_self() ); //线程分离

    while( 1 ) {
        //动态分配数据内存
        lnode = ( struct node* )malloc( sizeof( struct node ) );
        //分配失败
        if( lnode == NULL ) {
            printf("producer malloc node failed!\n");
            break;   
        }

        lnode->value = count++;

        pthread_mutex_lock( &mutex ); //占有锁

        lnode->next = head;
        head = lnode;

        printf("%u producer >> node %d\n", pthread_self(), lnode->value);

        pthread_mutex_unlock( &mutex ); //解锁

        pthread_cond_signal( &cond ); //发信号唤醒一个等待线程
        printf("%u usleep 1000000\n", pthread_self());
        sleep( 1 ); // 随眠1000毫秒
    }

    pthread_exit( NULL );
    return 0;
}

//消费者
static void *consumer( void *param ) {
    struct node *lnode = NULL;

    pthread_detach( pthread_self() ); //线程分离

    while( 1 ) {

        pthread_mutex_lock( &mutex );

        // while( head == NULL ) {
            printf("%u consumer cond wait\n", pthread_self());
            // pthread_cond_wait( &cond, &mutex ); //堵塞获取变量
            struct timespec ts;
            struct timeval tv;
            int wait_us = 100000, result; //堵塞等待微妙, 返回值
            long nsec; //纳秒

            gettimeofday( &tv, NULL ); //获取当前时间

            nsec = tv.tv_sec * 1000000000 + tv.tv_usec * 1000 + wait_us * 1000;
            ts.tv_nsec = nsec % 1000000000;
            ts.tv_sec = nsec / 1000000000;
            /*ts 时间为下次唤醒的绝对时间*/
            result = pthread_cond_timedwait( &cond, &mutex, &ts ); //堵塞获取变量
            switch (result) {
            case 0:
                printf("%u consumer wait success\n", pthread_self());
                break;
            case ETIMEDOUT:
                printf("%u consumer wait timeout\n", pthread_self());
                pthread_mutex_unlock( &mutex );
                continue;
                break;
            
            default:
                printf("%u consumer wait error\n", pthread_self());
                perror( "pthread_cond_timedwait" );
                pthread_mutex_unlock( &mutex );
                pthread_exit( NULL );
                break;
            }
        // }

        lnode = head;
        head = head->next;

        printf("%u consumer << node %d\n", pthread_self(), lnode->value);

        free( lnode ); //释放节点占用

        pthread_mutex_unlock( &mutex );

        printf("%u usleep 5000000\n", pthread_self());

        sleep( 5 ); // 随眠2秒

    }

    pthread_exit( NULL );
    return 0;
}

void check_result( char *str, int result ) {
    if( result == 0 ) {
        printf("%s success\n", str);
        return;
    }

    printf("%s failed code %d\n", str, result);
    return;
}

int main(int argc, char const *argv[])
{
    int result;

    result = pthread_mutex_init( &mutex, NULL );
    check_result( "mutex_init", result );
    result = pthread_cond_init( &cond, NULL );
    check_result( "cond_init", result );

    result = pthread_create( &tid_1, NULL, consumer, NULL );
    check_result( "consumer thread create", result );
    result = pthread_create( &tid_2, NULL, consumer, NULL );
    check_result( "consumer thread create", result );

    if( pthread_equal( tid_1, tid_2 ) ) {
        printf("tid_1 %u == tid_2 %u\n", tid_1, tid_2);
    }else{
        printf("tid_1 %u != tid_2 %u\n", tid_1, tid_2);
    }

    producer( NULL );

    return 0;
}