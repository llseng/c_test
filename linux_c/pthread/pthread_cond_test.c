/*
* @Author: llseng
* @Date:   2020-06-29 14:49:14
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-29 16:50:07
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

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

        pthread_mutex_unlock( &mutex ); //解锁
        printf("%u producer node %d\n", pthread_self(), lnode->value);

        pthread_cond_signal( &cond ); //发信号唤醒一个等待线程
        printf("%u usleep 10000\n", pthread_self());
        usleep( 100000 ); // 随眠100毫秒
    }

    pthread_exit( NULL );
    return 0;
}

//消费者
static void *consumer( void *param ) {
    struct node *lnode = NULL;

    pthread_detach( pthread_self() ); //线程分离

    pthread_mutex_lock( &mutex );

    while( 1 ) {

        while( head == NULL ) {
            printf("%u consumer cond wait\n", pthread_self());
            pthread_cond_wait( &cond, &mutex ); //堵塞获取变量
        }

        lnode = head;
        head = head->next;

        printf("%u consumer node %d\n", pthread_self(), lnode->value);

        free( lnode ); //释放节点占用
    }

    pthread_mutex_unlock( &mutex );

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

    producer( NULL );

    return 0;
}