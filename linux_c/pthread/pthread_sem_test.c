/*
* @Author: llseng
* @Date:   2020-06-30 10:18:56
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-30 11:18:39
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define SEM_MAX 10

static sem_t full_sem, empty_sem;

static pthread_t tid_1, tid_2;

void check_result( char *str, int result ) {
    if( result == 0 ) {
        printf("%s success\n", str);
        return;
    }

    printf("%s failed code %d\n", str, result);
    return;
}

static void *producer( void *param ) {
    int sval, result;
    pthread_t tid = pthread_self();
    pthread_detach( tid );

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

        printf("%u consumer code\n", tid);
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