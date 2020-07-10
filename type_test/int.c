/*
* @Author: llseng
* @Date:   2020-06-02 12:28:31
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-10 11:19:38
*/

#include <stdio.h>

int main( void ) {
    int a = 5, i;
    unsigned int b = 5;
    
    printf( "a-- %d\n", a-- );
    printf( "--b %d\n", --b );

    printf( "a %d\n", a );
    printf( "b %d\n", b );

    printf( "NULL %d\n", NULL );

    return 0;
}