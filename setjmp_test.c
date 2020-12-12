/*
* @Author: llseng
* @Date:   2020-06-02 11:38:48
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-02 11:52:45
*/

#include <stdio.h>
#include <setjmp.h>
#include <windows.h>

unsigned int num = 0;

void num_count( void ) {
    num++;
}

int main( int argc, char const *argv[] ) {
    static jmp_buf buf;

    if( setjmp( buf ) < 10 ) {
        num_count();
        printf("num = %d\n", num);
        longjmp( buf, num );
    }else{
        printf("jump exit\n");
    }

    return 0;
}