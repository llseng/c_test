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

int main(int argc, char const *argv[])
{
    int i, result;

    for (i = 0; i < 5; ++i)
    {
        result = gettimeofday( &tv, NULL );
        if( result != 0 ) {
            printf("gettimeofday error: %d\n", result);
        }

        printf("tv.tv_sec = %ld\n", tv.tv_sec);
        printf("tv.tv_usec = %ld\n", tv.tv_usec);

        usleep( 500000 );
    }

    return 0;
}