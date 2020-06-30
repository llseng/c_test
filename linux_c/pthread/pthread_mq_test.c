/*
* @Author: llseng
* @Date:   2020-06-30 12:21:08
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-30 18:20:30
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define THREAD_MAX 5
#define MQ_LEN_MAX 128
#define MQ_SIZE_MAX 128

static mqd_t mq;

static pthread_t tids[ THREAD_MAX ];

static void check_result( char *str, int result ) {
    if( result == 0 ) {
        printf("%s success\n", str);
        return;
    }

    printf("%s failed code %d\n", str, result);
    perror( str );
    return;
}

static void *producer( void *param ) {
    int result, count = 0;
    char buf[ MQ_SIZE_MAX ];

    pthread_t tid = pthread_self();
    pthread_detach( tid ); //分离线程

    while( ++count ) {
        snprintf( buf, sizeof( buf ), "%u producer node %d", tid, count );
        result = mq_send( mq, buf, MQ_SIZE_MAX, 0 );
        printf("%u producer ", tid);
        check_result( "mq_send", result );
        if( result != 0 ) {
            printf("%u producer exit!\n", tid);
            break;
        }
        printf("%u producer send %d\n", tid, count);

        usleep( 100000 );
    }

    pthread_exit( NULL );

}

static void *consumer( void *param ) {
    int result, count = 0;
    char buf[ MQ_SIZE_MAX ];

    pthread_t tid = pthread_self();
    pthread_detach( tid ); //分离线程

    while( 1 ) {
        result = mq_receive( mq, buf, MQ_SIZE_MAX, 0 );
        if( result < 0 ) {
            printf("%u consumer ", tid);
            check_result( "mq_receive", result );
        }
        if( result < 0 ) {
            printf("%u consumer exit!\n", tid);
            break;
        }
        printf("%u consumer receive %s\n", tid, buf);
        usleep( 1000000 );
    }

    pthread_exit( NULL );

}

int main(int argc, char const *argv[])
{

    struct mq_attr mqAttr;
    char mq_name[] = "/mq_test";

    memset( &mqAttr, 0, sizeof( mqAttr ) ); //数据置零
    mqAttr.mq_flags = 0;
    mqAttr.mq_maxmsg = MQ_LEN_MAX; /*队列属性受  /proc/sys/fs/mqueue/ 配置限制 root用户不受限制*/
    mqAttr.mq_msgsize = MQ_SIZE_MAX;

    mq = mq_open( mq_name, O_RDWR | O_CREAT, 0777, &mqAttr ); //打开队列
    // mq = mq_open( "/mq_test", 0 );
    printf("O_CREAT %d ,O_EXCL %d\n", O_CREAT, O_EXCL);
    printf("mq = %d\n", mq);
    if( mq < 0 ) {
        check_result("mq_open", mq );
        return 0;
    }

    mq_unlink( mq_name ); //分离队列 之后若持有计数为 0，则删除消息队列 (未分离则存在于外存, 可与其他或下一次程序共享)

    int i, result;

    for (i = 0; i < THREAD_MAX; ++i)
    {
        result = pthread_create( &tids[ i ], NULL, producer, NULL );
        check_result( "producer thread created", result );
        if( result != 0 ) continue;
        printf("tids[ %d ] = %u\n",i, tids[ i ] );
    }

    consumer( NULL );

    return 0;
}