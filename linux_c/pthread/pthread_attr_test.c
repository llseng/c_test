/*
* @Author: llseng
* @Date:   2020-07-01 11:15:25
* @Last Modified by:   llseng
* @Last Modified time: 2020-07-01 17:33:59
*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_MAX 10

extern int errno;

static pthread_t tids[ THREAD_MAX ], tid_1; //线程ID

static pthread_attr_t tids_attr[ THREAD_MAX ], tid_1_attr; //线程属性

static pthread_mutex_t mutex; //锁

static struct sched_param scheds[ THREAD_MAX ], *sched_p; //优先级

static int count = 0; //计数

/*验证返回*/
static void check_result( char *str, int result ) {
    if( result == 0 ) {
        printf("%s success\n", str);
        return;
    }

    printf("%s failed code %d\n", str, result);
    printf("Error %d: %s\n", errno, strerror(errno));
    return;
}

/*读取*/
static void *read_run( void *param ) {
    int lable = *(int *)param;

    printf("read_%d start\n", lable);

    pthread_setcancelstate( PTHREAD_CANCEL_ENABLE, NULL ); //   有两种值：PTHREAD_CANCEL_ENABLE：取消使能 PTHREAD_CANCEL_DISABLE：取消不使能（线程创建时的默认值）
    // pthread_setcanceltype( PTHREAD_CANCEL_DEFFERED, NULL ); //有 2 种值：PTHREAD_CANCEL_DEFFERED：线程收到取消请求后继续运行至下一个取消点再结束（线程创建时的默认值）。 PTHREAD_CANCEL_ASYNCHRONOUS：线程立即结束

    while( 1 ) {
        printf("read_%d cancel A\n", lable);

        pthread_testcancel(); //设置取消点

        printf("read_%d cancel B\n", lable);

        pthread_mutex_lock( &mutex ); //占有锁

        printf("read_%d count = %d\n", lable, count);

        pthread_mutex_unlock( &mutex ); //释放锁

        usleep( 900000 ); //随眠 900 毫秒
    }

    pthread_exit( NULL );

}

static void *write_run( void *param ) {

    int lable = *(int *)param, i, result;

    printf("write_%d start\n", lable);

    while( 1 ) {
        printf("write_%d wa\n", lable);

        pthread_mutex_lock( &mutex ); //占有锁

        printf("write_%d waa\n", lable);

        printf("write_%d count %d\n", lable, count);

        if( count == lable ) {
            printf("write_%d wf\n", lable);
            for (i = 0; i < THREAD_MAX; ++i)
            {
                result = pthread_cancel( tids[ i ] );
                printf("tids[ %d ] %u ", i, tids[ i ]);
                check_result( "pthread_cancel", result );
                if( result != 0 ) {
                    printf("pthread_cancel %d break\n", i);
                    break;
                }
            }
            printf("write_%d wfd\n", lable);

            // pthread_mutex_unlock( &mutex ); //释放锁

            // break;
        }

        printf("write_%d count = %d\n", lable, ++count);

        printf("write_%d wb\n", lable);

        pthread_mutex_unlock( &mutex ); //释放锁

        printf("write_%d wc\n", lable);

        usleep( 1000000 ); //随眠 1000 毫秒
    }

    pthread_exit( NULL );
}

int main(int argc, char const *argv[])
{
    int i, result;

    pthread_mutex_init( &mutex, NULL ); //初始化锁

    for (i = 0; i < THREAD_MAX; ++i)
    {
        printf(">> read thread %d\n", i);

        pthread_t *thread_p = &tids[ i ];
        pthread_attr_t *attr_p = &tids_attr[ i ];
        // pthread_attr_t *attr_p = tids_attr + i;

        result = pthread_attr_init( attr_p ); //线程属性初始化
        check_result( "pthread_attr_init", result );
        if( result != 0 ) {
            printf("read thread %d break\n", i);
            break;
        }

        result = pthread_attr_setdetachstate(attr_p, PTHREAD_CREATE_DETACHED); //线程分离状态 PS: PTHREAD_CREATE_JOIDABLE(非分离 默认) PTHREAD_CREATE_DETACHED(分离)
        check_result( "pthread_attr_setdetachstate", result );
        if( result != 0 ) {
            printf("read thread %d break\n", i);
            break;
        }

        result = pthread_attr_setschedpolicy(attr_p, SCHED_FIFO); //线程分离状态 PS: SCHED_OTHER（正常、非实时 不支持优先级) SCHED_RR（实时、轮转法）SCHED_FIFO（实时、先入先出）
        check_result( "pthread_attr_setschedpolicy", result );
        if( result != 0 ) {
            printf("read thread %d break\n", i);
            break;
        }

        /*
        result = pthread_attr_setinheritsched(attr_p, PTHREAD_EXPLICIT_SCHED); //设定线程的继承性，如果需要认为设定线程的调度策略和优先级，必须将线程的继承策略设定为
        //PTHREAD_EXPLICIT_SCHED;不然默认值为PTHREAD_INHERIT_SCHED，表示新线程继承创建线程调度策略和参数;
        //该函数必须在root权限才能正常调用;
        check_result( "pthread_attr_setinheritsched", result );
        if( result != 0 ) {
            printf("read thread %d break\n", i);
            break;
        }
        */

        sched_p = &scheds[ i ];
        result = pthread_attr_getschedparam(attr_p, sched_p); //获取线程调度参数
        check_result( "pthread_attr_getschedparam", result );
        if( result != 0 ) {
            printf("read thread %d break\n", i);
            break;
        }

        sched_p->sched_priority = i + 80; //优先级
        printf("sched_p->sched_priority %d\n", sched_p->sched_priority);
        result = pthread_attr_setschedparam(attr_p, sched_p); //设置线程调度参数 PS: 一般为 1 - 99  数值越大 优先级越高
        check_result( "pthread_attr_setschedparam", result );
        if( result != 0 ) {
            printf("read thread %d break\n", i);
            break;
        }

        result = pthread_attr_setscope(attr_p, PTHREAD_SCOPE_SYSTEM); //线程间竞争CPU的范围 PS: PTHREAD_SCOPE_PROCESS（进程内竞争资源）PTHREAD_SCOPE_SYSTEM （系统级竞争资源）Linux支持 PTHREAD_SCOPE_SYSTEM
        check_result( "pthread_attr_setscope", result );
        if( result != 0 ) {
            printf("read thread %d break\n", i);
            break;
        }

        result = pthread_create( thread_p, attr_p, read_run, (void *)&i );
        check_result( "pthread_create", result );
        switch( result ) {
            case 0:
                printf("pthread_create 0\n");
            break;

            case EINVAL:
                printf("pthread_create EINVAL\n");
            break;

            case ENOMEM:
                printf("pthread_create ENOMEM\n");
            break;

            default:
                printf("pthread_create other\n");
            break;
        }
        if( result != 0 ) {
            printf("read thread %d break\n", i);
            break;
        }

        printf("read thread %d <<\n", i);
    }

    i = 1;
    write_run( (void *)&i );

    return 0;
}