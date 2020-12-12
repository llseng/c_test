/*
* @Author: llseng
* @Date:   2020-06-29 17:40:47
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-29 18:22:24
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_MAX 10

static pthread_rwlock_t rwlock;

static pthread_t tids[ THREAD_MAX ];

static data = 0;

static void *write_run( void *param ) {
    pthread_detach( pthread_self() ); //分离

    int result;

    while( 1 ) {
        result = pthread_rwlock_wrlock( &rwlock ); //写锁

        if( result != 0 ) {
            printf("%u write_run rwlock_wrlock failed\n", pthread_self());
            break;
        }

        data++;
        printf("%u write_run write data %d...\n", pthread_self(), data);
        sleep( 2 );
        printf("write success\n");

        pthread_rwlock_unlock( &rwlock ); //解锁
        sleep( 5 );
        printf("%u write_run sleep 5\n", pthread_self());
    }

    pthread_exit( NULL );
}

static void *read_run( void *param ) {
    pthread_detach( pthread_self() ); //分离

    int result;

    while( 1 ) {
        result = pthread_rwlock_rdlock( &rwlock ); //读锁

        if( result != 0 ) {
            printf("%u read_run rwlock_rdlock failed\n", pthread_self());
            break;
        }

        printf("%u read_run read data %d\n", pthread_self(), data);
        printf("%u read_run sleep 1\n", pthread_self());

        pthread_rwlock_unlock( &rwlock ); //解锁
        sleep( 1 );
    }

    pthread_exit( NULL );

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
    int i, result;

    pthread_rwlock_init( &rwlock, NULL ); //初始化读写锁

    for (i = 0; i < THREAD_MAX; ++i)
    {
        result = pthread_create( &tids[ i ], NULL, read_run, NULL );
        check_result( "read_run thread create", result );
        printf("tids[ %d ] : %u\n", i, tids[ i ]);
    }

    write_run( NULL );

    return 0;
}