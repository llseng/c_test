/*
* @Author: llseng
* @Date:   2020-07-02 14:15:19
* @Last Modified by:   llseng
* @Last Modified time: 2020-07-02 14:24:34
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

static struct timeval tv;

static struct timespec ts;

int main(int argc, char const *argv[])
{
    printf( "long len %d\n", sizeof(long) );

    int i, result;

    for (i = 0; i < 5; ++i)
    {
        result = gettimeofday( &tv, NULL );
        if( result != 0 ) {
            printf("gettimeofday error: %d\n", result);
        }

        printf("tv.tv_sec = %lu\n", tv.tv_sec);
        printf("tv.tv_usec = %lu\n", tv.tv_usec);

        usleep( 500000 );
    }

    for ( i = 0; i < 5; i++)
    {
        result = gettimeofday( &tv, NULL );
        if( result != 0 ) {
            printf("gettimeofday error: %d\n", result);
        }

        printf("-tv.tv_sec = %lu\n", tv.tv_sec);
        printf("-tv.tv_usec = %lu\n", tv.tv_usec);

        long long wns = 100000000;
        ts.tv_sec = wns / 1000000000;
        ts.tv_nsec = wns % 1000000000;

        printf("-ts.tv_sec = %lu\n", ts.tv_sec);
        printf("-ts.tv_nsec = %lu\n", ts.tv_nsec);
        
        nanosleep( &ts, NULL ); // 随眠 100000000 纳秒

    }

    
    result = gettimeofday( &tv, NULL );
    if( result != 0 ) {
        printf("gettimeofday error: %d\n", result);
    }
    printf("--tv.tv_sec = %lu\n", tv.tv_sec);
    printf("--tv.tv_usec = %lu\n", tv.tv_usec);
    
    long long wns = 10000000000;
    ts.tv_sec = wns / 1000000000;
    ts.tv_nsec = wns % 1000000000;

    printf("--ts.tv_sec = %lu\n", ts.tv_sec);
    printf("--ts.tv_nsec = %lu\n", ts.tv_nsec);
    
    nanosleep( &ts, NULL ); // 随眠 10000000000 纳秒
    
    printf( "sleep 10\n" );
    sleep( 10 );

    return 0;
}