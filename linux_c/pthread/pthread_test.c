#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define FNUM 10

int fnum = 0;
//互斥锁
pthread_mutex_t fnum_mutex;

void *thread_run( void *arg ) {
    pthread_t thrid;
    pid_t pid;
    int i;

    thrid = pthread_self();
    pid = getpid();
    //分离线程 (自动释放线程资源)
    pthread_detach( thrid );

    for (i = 0; i < FNUM; ++i)
    {
        //占有锁
        pthread_mutex_lock( &fnum_mutex );
        fnum++;
        if( (int *)arg ) {
            printf( "master_" );
        }
        printf("thread:%u; fnum:%u;\n", thrid, fnum );
        //释放锁
        pthread_mutex_unlock( &fnum_mutex );
        // sleep( 1 );
    }
    pthread_exit( NULL );
}

int main( int argc, const char *argv[] ) {
    int thread_create_status;
    pthread_t tid;
    void *req;
    int i;

	printf("pid%u\n", getpid() );
    //初始化锁
    pthread_mutex_init( &fnum_mutex, NULL );

    for (i = 0; i < FNUM; ++i)
    {
        //创建线程
        thread_create_status = pthread_create( &tid, NULL, thread_run, NULL );

        if( thread_create_status != 0 ) {
            printf("pthread_create error: %u\n", thread_create_status);
        }

        // pthread_join( tid, &req );
        printf("pthread_create: %u;pthread_exit %u;\n", tid, req);
    }

    thread_run( (void *)1 );
}