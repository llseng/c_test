/*
 * @Author: llseng 
 * @Date: 2020-07-07 16:44:16 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-13 16:27:51
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "thread_pool.h"
#include "logger.h"

#define DEBUG 1

#if DEBUG
#include "thread_pool.c"
#include "logger.c"
#endif


static wm_logger_t logger;
static wm_logger_handler_t log_handler;

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
    wm_log_info( &logger, "test_func arg = %d start", *(int *)arg );

    int i;
    for( i = 0; i < 1000; i++ ) {
        wm_log_info( &logger, "test_func arg = %d > %d", *(int *)arg, i );
    }

    // sleep( *(int *)arg );
    printf( "test_func arg = %d end\n", *(int *)arg );
    wm_log_info( &logger, "test_func arg = %d end", *(int *)arg );
    free( arg );
}

int main(int argc, char const *argv[])
{
    printf( "test main start\n" );

    int res, i;

    wm_logger_init( &logger, "logger_test" );
    wm_logger_handler_init( &log_handler, "log_test.log", LOG_DEBUG );
    wm_logger_add_handler( &logger, &log_handler );
    wm_logger_handler_set_max_file_size( &log_handler, 10485760 );
    i = 1000000;
    while( i-- ) {
        wm_log_info( &logger, "'c:\\Users\\Administrator\\.vscode\\extensions\\ms-vscode.cpptools-0.29.0-insiders2\\debugAdapters\\bin\\WindowsDebugLauncher.exe' '--stdin=Microsoft-MIEngine-In-dqtqpesa.c0f' '--stdout=Microsoft-MIEngine-Out-hydghudb.est' '--stderr=Microsoft-MIEngine-Error-zsiqakoi.cvr' '--pid=Microsoft-MIEngine-Pid-jqtno3k4.0vm' '--dbgExe=D:\\Dev-Cpp\\MinGW64\\bin\\gdb.exe' '--interpreter=mi'" );
    }

    return 0;

    wm_thread_pool_t pool;

    res = wm_thread_pool_init( &pool );
    check_result("wm_thread_pool_init", res);
    if( res != 0 ) return 0;

    res = wm_thread_pool_set_idle_msec( &pool, 5000 );
    check_result("wm_thread_pool_set_idle_msec", res);
    if( res != 0 ) return 0;

    res = wm_thread_pool_set_poll_msec( &pool, 500 );
    check_result("wm_thread_pool_set_poll_msec", res);
    if( res != 0 ) return 0;

    res = wm_thread_pool_set_max_idle_count( &pool, 10 );
    check_result("wm_thread_pool_set_max_idle_count", res);
    if( res != 0 ) return 0;

    res = wm_thread_pool_set_max_thread_count( &pool, 100 );
    check_result("wm_thread_pool_set_max_idle_count", res);
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

    // res = wm_thread_pool_shutdown( &pool );
    // check_result("wm_thread_pool_shutdown", res);
    // if( res != 0 ) return 0;

    while( 1 ) {
        sleep( 1 );
        printf( "task = %u thread = %u idle_thread = %u\n", pool.task_count, pool.thread_count, pool.idle_thread_count );

        wm_log_info( &logger, "task = %u thread = %u idle_thread = %u", pool.task_count, pool.thread_count, pool.idle_thread_count );

        fflush( stdout );
    }

    return 0;
}
