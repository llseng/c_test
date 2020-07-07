/*
 * @Author: llseng 
 * @Date: 2020-07-06 16:01:01 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-07 16:18:14
 */
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include "thread_pool.h"

wm_thread_pool_task_t *wm_thread_pool_malloc_task( void *(*func)(void *), void *param, wm_thread_pool_task_t *next ) {
    wm_thread_pool_task_t *task = (wm_thread_pool_task_t *)malloc( sizeof( wm_thread_pool_task_t ) );
    if( task == NULL ) return NULL;

    task->func = func;
    task->param = param;
    task->next = next;

    return task;
}

void *wm_thread_pool_manager_run( void *arg ) {
    wm_thread_pool_t *pool = (wm_thread_pool_t *)arg;
    
    struct timespec req;
    req.tv_sec = 0;
    req.tv_nsec = 100000000;

    while ( 1 )
    {
        if( wm_thread_pool_lock( pool ) != 0 ) break;

        int i, lave_idle_count, lave_thread_count, wait_create_count;
        lave_idle_count = pool->max_idle_count - pool->idle_thread_count;
        lave_thread_count = pool->max_thread_count - pool->thread_count;
        wait_create_count = lave_thread_count >= lave_idle_count? lave_idle_count: lave_thread_count;

        for( i = 0; i < wait_create_count; i++ ) {
            pthread_t worker_tid;
            pthread_attr_t worker_attr;
            /*创建工作线程*/
            if( pthread_attr_init( &worker_attr ) != 0 ) break;
            if( pthread_attr_setdetachstate( &worker_attr, PTHREAD_CREATE_DETACHED ) != 0 ) break;
            if( pthread_create( &worker_tid, &worker_attr, wm_thread_pool_worker_run, arg ) != 0 ) break;

            pool->thread_count++;
        }

        if( wm_thread_pool_unlock( pool ) != 0 ) break;
    
        if( nanosleep( &req, NULL ) != 0 ) break;
    }

    pthread_exit( NULL );
}

void *wm_thread_pool_worker_run( void *arg ) {
    wm_thread_pool_t *pool = (wm_thread_pool_t *)arg;

    int result;
    wm_thread_pool_task_t *task;

    while( 1 ) {
        if( wm_thread_pool_lock( pool ) != 0 ) break;

        pool->idle_thread_count++;

        result = wm_thread_pool_timedwait( pool, pool->idle_msec );
        /*线程池关闭*/
        if( pool->shutdown ) {
            pool->thread_count--;
            pool->idle_thread_count--;
            if( wm_thread_pool_unlock( pool ) != 0 ) break;
            break;
        }

        if( result == 0 ) {
            /*任务通知信号*/
            if( pool->task_head == pool->task_tail ) {
                task = NULL;
            }else{
                task = pool->task_head->next;
                pool->task_head->next = task->next;
                pool->task_count--;
            }

            if( pool->task_head->next == NULL ) {
                pool->task_tail = pool->task_head;
                pool->task_count = 0;
            }
        }else if( result == ETIMEDOUT ) {
            /*等待通知信号超时*/
            if( pool->idle_thread_count > pool->max_idle_count ) {
                pool->thread_count--;
                pool->idle_thread_count--;
                if( wm_thread_pool_unlock( pool ) != 0 ) break;
                break;
            }
        }else{
            if( wm_thread_pool_unlock( pool ) != 0 ) break;
            break;
        }

        pool->idle_thread_count--;
        if( wm_thread_pool_unlock( pool ) != 0 ) break;

        if( task != NULL ) task->func( task->param ); //执行任务

        free( task );

    }

    pthread_exit( NULL );
}

int wm_thread_pool_init( wm_thread_pool_t *pool ) {
    wm_thread_pool_task_t *start_task = wm_thread_pool_malloc_task(NULL, NULL, NULL);
    if( start_task == NULL ) return 1;

    if( pthread_attr_init( &pool->manager_attr ) != 0 ) return -3;
    if( pthread_cond_init( &pool->cond, NULL ) != 0 ) return -1;
    if( pthread_mutex_init( &pool->mutex, NULL ) != 0 ) return -2;

    pool->task_head = start_task;
    pool->task_tail = start_task;

    pool->task_count = 0;
    pool->thread_count = 0;
    // pool->busy_thread_count = 0;
    pool->idle_thread_count = 0;

    pool->idle_msec = 1000000;
    pool->max_thread_count = 1024;
    pool->max_idle_count = 4;

    pool->shutdown = 0;

    /*创建管理线程*/
    if( pthread_attr_setdetachstate( &pool->manager_attr, PTHREAD_CREATE_DETACHED ) != 0 ) return -4;
    if( pthread_create( &pool->manager_tid, &pool->manager_attr, wm_thread_pool_manager_run, (void *)pool ) != 0 ) return -5;

    return 0;
}

int wm_thread_pool_add_task( wm_thread_pool_t *pool, void *(*func)(void *), void *param ) {
    wm_thread_pool_task_t *new_task = wm_thread_pool_malloc_task(func, param, NULL);
    if( new_task == NULL ) return 1;
    
    if( wm_thread_pool_lock( pool ) != 0 ) return 2;

    pool->task_tail->next = new_task;
    pool->task_tail = new_task;
    pool->task_count++;

    if( wm_thread_pool_unlock( pool ) != 0 ) return 3;

    if( wm_thread_pool_signal( pool ) != 0 ) return 4;

    return 0;
}

int wm_thread_pool_pop_task( wm_thread_pool_t *pool, wm_thread_pool_task_t *task ) {
    if( wm_thread_pool_lock( pool ) != 0 ) return 1;

    if( pool->task_head == pool->task_tail ) {
        task = NULL;
    }else{
        task = pool->task_head->next;
        pool->task_head->next = task->next;
        pool->task_count--;
    }

    if( pool->task_head->next == NULL ) {
        pool->task_tail = pool->task_head;
        pool->task_count = 0;
    }

    if( wm_thread_pool_unlock( pool ) != 0 ) return 2;

    return 0;
}


int wm_thread_pool_shutdown( wm_thread_pool_t *pool ) {
    if( wm_thread_pool_lock( pool ) != 0 ) return 1;

    pool->shutdown = 1;
    wm_thread_pool_broadcast( pool );

    if( wm_thread_pool_unlock( pool ) != 0 ) return 2;

    return 0;
}

int wm_thread_pool_set_idle_msec( wm_thread_pool_t *pool, unsigned int msec ) {
    if( wm_thread_pool_lock( pool ) != 0 ) return 1;

    pool->idle_msec = msec;

    if( wm_thread_pool_unlock( pool ) != 0 ) return 2;

    return 0;
}

/*
int wm_thread_pool_lock( wm_thread_pool_t *pool ) {
    return pthread_mutex_lock( &pool->mutex );
}

int wm_thread_pool_unlock( wm_thread_pool_t *pool ) {
    return pthread_mutex_unlock( &pool->mutex );
}

int wm_thread_pool_signal( wm_thread_pool_t *pool ) {
    return pthread_cond_signal( &pool->cond );
}

int wm_thread_pool_broadcast( wm_thread_pool_t *pool ) {
    return pthread_cond_broadcast( &pool->cond );
}

int wm_thread_pool_wait( wm_thread_pool_t *pool ) {
    return pthread_cond_wait( &pool->cond, &pool->mutex );
}
*/

int wm_thread_pool_timedwait( wm_thread_pool_t *pool, unsigned int msec ) {
    struct timeval tv;
    struct timespec ts;
    long nsec;
    
    if( gettimeofday( &tv, NULL ) != 0 ) return -1;
    nsec = ( msec % 1000 ) * 1000000 + tv.tv_usec * 1000;

    ts.tv_sec = tv.tv_sec + msec / 1000 + nsec / 1000000000;
    ts.tv_nsec = nsec % 1000000000;

    return pthread_cond_timedwait( &pool->cond, &pool->mutex, &ts );
}