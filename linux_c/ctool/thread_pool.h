/*
 * @Author: llseng 
 * @Date: 2020-07-03 17:39:02 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-07 16:14:35
 */
#ifndef PTHREAD_H

#define PTHREAD_H
#include <pthread.h>

#endif

struct wm_thread_pool_task {
    void *(*func)(void *);
    void *param;
    struct wm_thread_pool_task *next;
};
/**
 * 任务结构体
 */
typedef struct wm_thread_pool_task wm_thread_pool_task_t;

struct wm_thread_pool {
    pthread_t manager_tid;
    pthread_attr_t manager_attr;
    pthread_cond_t cond;
    pthread_mutex_t mutex;

    wm_thread_pool_task_t *task_head;
    wm_thread_pool_task_t *task_tail;
    unsigned int task_count; //节点数量

    unsigned int thread_count; //线程数量
    // unsigned int busy_thread_count; //忙碌线程数量
    unsigned int idle_thread_count; //闲置线程数量

    unsigned int idle_msec; //闲置毫秒时间
    unsigned int max_thread_count; //最大线程数
    unsigned int max_idle_count; //最大闲置线程数

    unsigned int shutdown; //关闭
};
/**
 * 线程池结构体
 */
typedef struct wm_thread_pool wm_thread_pool_t;

wm_thread_pool_task_t *wm_thread_pool_malloc_task( void *(*func)(void *), void *param, wm_thread_pool_task_t *next );

void *wm_thread_pool_manager_run( void *arg );

void *wm_thread_pool_worker_run( void *arg );

int wm_thread_pool_init( wm_thread_pool_t *pool );

int wm_thread_pool_add_task( wm_thread_pool_t *pool, void *(*func)(void *), void *param );

int wm_thread_pool_pop_task( wm_thread_pool_t *pool, wm_thread_pool_task_t *task );

int wm_thread_pool_shutdown( wm_thread_pool_t *pool );

int wm_thread_pool_set_idle_msec( wm_thread_pool_t *pool, unsigned int msec );

#define wm_thread_pool_lock( pool ) pthread_mutex_lock( &(pool)->mutex )
// int wm_thread_pool_lock( wm_thread_pool_t *pool );

#define wm_thread_pool_unlock( pool ) pthread_mutex_unlock( &(pool)->mutex )
// int wm_thread_pool_unlock( wm_thread_pool_t *pool );

#define wm_thread_pool_signal( pool ) pthread_cond_signal( &(pool)->cond )
// int wm_thread_pool_signal( wm_thread_pool_t *pool );

#define wm_thread_pool_broadcast( pool ) pthread_cond_broadcast( &(pool)->cond )
// int wm_thread_pool_broadcast( wm_thread_pool_t *pool );

#define wm_thread_pool_wait( pool ) pthread_cond_wait( &(pool)->cond, &(pool)->mutex )
// int wm_thread_pool_wait( wm_thread_pool_t *pool );

int wm_thread_pool_timedwait( wm_thread_pool_t *pool, unsigned int msec );