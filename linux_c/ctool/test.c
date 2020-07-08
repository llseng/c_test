/*
 * @Author: llseng 
 * @Date: 2020-07-07 16:44:16 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-07 16:45:03
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "thread_pool.h"
// #include "thread_pool.c"

static void check_result( char *str, int result ) {
    if( result == 0 ) {
        printf("%s success\n", str);
        return;
    }

    printf("%s failed code %d\n", str, result);
    return;
}

static void * test_func(void *arg) {
    printf( "test_func arg = %d start\n", *(int *)arg );
    sleep( *(int *)arg );
    printf( "test_func arg = %d end\n", *(int *)arg );
    free( arg );
}

int main(int argc, char const *argv[])
{
    printf( "test main start\n" );

    int res, i;

    wm_thread_pool_t pool;

    res = wm_thread_pool_init( &pool );
    check_result("wm_thread_pool_init", res);
    if( res != 0 ) return 0;
    res = wm_thread_pool_set_idle_msec( &pool, 5000 );
    check_result("wm_thread_pool_set_idle_msec", res);
    if( res != 0 ) return 0;

    for ( i = 0; i < 100; i++)
    {
        int *i_p = (int *)malloc( sizeof( int ) );
        *i_p = i;
        res = wm_thread_pool_add_task( &pool, test_func, (void *)i_p );
        check_result("wm_thread_pool_add_task", res);
        if( res != 0 ) return 0;
    }
    i = 1;
    while( i-- ) {
        sleep( 1 );
        printf( "task = %u thread = %u idle_thread = %u\n", pool.task_count, pool.thread_count, pool.idle_thread_count );
        fflush( stdout );
    }

    res = wm_thread_pool_shutdown( &pool );
    check_result("wm_thread_pool_shutdown", res);
    if( res != 0 ) return 0;
    
    while( 1 ) {
        sleep( 1 );
        printf( "task = %u thread = %u idle_thread = %u\n", pool.task_count, pool.thread_count, pool.idle_thread_count );
        fflush( stdout );
    }

    return 0;
}
