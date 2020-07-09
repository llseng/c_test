/*
* @Author: llseng
* @Date:   2020-06-02 12:28:31
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-09 18:21:45
*/

#include <stdio.h>

int main( void ) {
    int a = 5, i;
    unsigned int b = 5;
    
    printf( "a-- %d\n", a-- );
    printf( "--b %d\n", --b );

    printf( "a %d\n", a );
    printf( "b %d\n", b );
    return 0;
}