/*
* @Author: llseng
* @Date:   2020-06-30 10:18:56
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-30 11:36:42
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define SEM_MAX 10
/*互斥锁 保护共享数据*/
static pthread_mutex_t mutex;
/*信号量 线程通信*/
static sem_t full_sem, empty_sem;

static pthread_t tid_1, tid_2;

struct node {
    int value;
    struct node *next;
};
static struct node* head = NULL;

void check_result( char *str, int result ) {
    if( result == 0 ) {
        printf("%s success\n", str);
        return;
    }

    printf("%s failed code %d\n", str, result);
    return;
}

static void *producer( void *param ) {
    int sval, result, count = 0;
    pthread_t tid = pthread_self();
    pthread_detach( tid );
    struct node* lnode;

    while( 1 ) {
        result = sem_getvalue( &full_sem, &sval );
        printf("%u producer", tid);
        check_result( " get full_sval", result );
        if( result != 0 ) break;

        printf("%u producer full_sval %d\n", tid, sval);
        if( sval >= SEM_MAX ) {
            printf("%u producer wait empty_sem...\n", tid);
            sem_wait( &empty_sem ); //等待空信号
            continue;
        }

        lnode = (struct node *)malloc( sizeof( struct node ) );
        if( lnode == NULL ) {
            printf("%u producer malloc node failed\n", tid);
            break;
        }

        lnode->value = count++;

        pthread_mutex_lock( &mutex ); //加锁

        lnode->next = head;
        head = lnode;

        pthread_mutex_unlock( &mutex ); //解锁

        printf("%u producer post full_sem...\n", tid);
        result = sem_post( &full_sem ); //发送队列信号
        printf("%u producer", tid);
        check_result( " wait full", result );
        if( result != 0 ) break;

    }

    pthread_exit( NULL );
}

static void *consumer( void *param ) {
    int sval, result;
    pthread_t tid = pthread_self();
    pthread_detach( tid );
    struct node *lnode;

    while( 1 ) {
        result = sem_getvalue( &full_sem, &sval );
        printf("%u consumer", tid);
        check_result( " get full_sval", result );
        if( result != 0 ) break;

        printf("%u consumer sval %d\n", tid, sval);
        if( sval == 0 ) {
            sem_post( &empty_sem );
            usleep( 10000000 );
            continue;
        }

        printf("%u consumer wait full_sem...\n", tid);
        result = sem_wait( &full_sem );
        printf("%u consumer", tid);
        check_result( " wait full", result );
        if( result != 0 ) break;

        pthread_mutex_lock( &mutex );

        lnode = head;
        head = head->next;

        pthread_mutex_unlock( &mutex );

        printf("%u consumer code %d\n", tid, lnode->value);
        free( lnode );
        usleep( 1000000 );
    }

}

int main(int argc, char const *argv[])
{
    int result;

    result = pthread_create( &tid_1, NULL, consumer, NULL );
    check_result( "consumer thread created", result );
    result = pthread_create( &tid_2, NULL, consumer, NULL );
    check_result( "consumer thread created", result );

    producer( NULL );

    return 0;
}