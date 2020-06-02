/*
* @Author: llseng
* @Date:   2020-06-02 14:52:23
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-02 15:57:34
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main( int argc, char const *argv[] ) {

    int i = 101;
    int k = 0;
    char bar[102] = {0};
    char s[] = "-\\|/";

    while( i-- ) {
        printf( "[%-100s][%d%%][%c]\r", bar, k, s[k%4] );
        fflush( stdout );
        usleep( 100000 );
        bar[k++] = '=';
        bar[k] = '\0';
    }
    printf( "\n" );
    return 0;
}