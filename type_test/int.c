/*
* @Author: llseng
* @Date:   2020-06-02 12:28:31
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-10 11:19:38
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float randMod( void ); 

int main( void ) {
    int a = 5, i;
    unsigned int b = 5;
    
    printf( "a-- %d\n", a-- );
    printf( "--b %d\n", --b );

    printf( "a %d\n", a );
    printf( "b %d\n", b );

    printf( "NULL %d\n", NULL );

    printf( "RAND_MAX %d\n", RAND_MAX );

    time_t now_time = time( NULL );

    printf( "now_time %13lld\n", now_time );
    
    srand( now_time );

    i = 5;
    while( i-- ) {
        
        printf( "rand %06d\n", rand() );
        printf( "rand2 %04d\n", rand() % 10000 );

        printf( "randMod %.3f\n", randMod() );
    }

    return 0;
}

float randMod( void ) {
    int rand_num;
    float n;
    rand_num = rand();
    n = (float)(rand_num % 10000) / 10000;

    return n;
}