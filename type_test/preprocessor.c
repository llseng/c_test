/*
 * @Author: llseng 
 * @Date: 2020-07-07 10:06:59 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-07 10:24:59
 */
#include <stdio.h>

static int return_int( int i ) {
    printf( "return_int i = %d\n", i );

    return i;
}

#define return_int_1( i ) { return_int( ( i ) ); }
#define return_int_2( i ) { return return_int( ( i ) ); }
#define return_int_3( i ) return_int( ( i ) )
#define return_int_4( i ) ( return_int( ( i ) ) )
#define return_int_5( i ) ( i )
#define return_int_6( i ) printf( "printf i = %d\n", (i) )

int main(int argc, char const *argv[])
{
    int i = 1;
    // printf( "return_int_1( %d ) = %d\n", i, return_int_1( i ) );
    // printf( "return_int_2( %d ) = %d\n", i, return_int_2( i ) );
    printf( "return_int_3( %d ) = %d\n", i, return_int_3( i ) );
    i++;
    printf( "return_int_4( %d ) = %d\n", i, return_int_4( i ) );
    i++;
    printf( "return_int_5( %d ) = %d\n", i, return_int_5( i ) );
    i++;
    printf( "return_int_6( %d ) = %d\n", i, return_int_6( i ) );
    return 0;
}
