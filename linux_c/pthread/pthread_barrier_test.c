/*
* @Author: llseng
* @Date:   2020-06-29 18:36:39
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-29 19:14:11
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_MAX 3

static pthread_t tids[ THREAD_MAX ];

static pthread_barrier_t barrier; //屏障

static void *thread_run( void *param ) {
    pthread_detach( pthread_self() ); //分离

    printf("thread_%d run...\n", param);
    sleep( (unsigned long)param );

    printf("thread_%d wait other thread\n", param);
    pthread_barrier_wait( &barrier );

    printf("thread_%d start...\n", param);

    pthread_exit( NULL ); //结束
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
    int result, i;
    unsigned long seconds = 1;

    pthread_barrier_init( &barrier, NULL, THREAD_MAX );

    for (i = 0; i < THREAD_MAX; ++i)
    {
        result = pthread_create( &tids[ i ], NULL, thread_run, (void *)seconds );
        printf("thread_%d ", seconds);
        check_result(" created", result);
        printf("tids[ %d ] : %u\n", i, tids[ i ]);

        seconds++;
    }

    sleep( seconds );
    printf("exit\n");

    return 0;
}