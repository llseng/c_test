/*
* @Author: llseng
* @Date:   2020-06-02 12:28:31
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-02 12:31:58
*/

#include <stdio.h>

int main( void ) {
    int a = 5, i;
    unsigned int b = 5;

    for (i = 0; i < 6; i++)
    {
        a--;
        b--;

        printf("a = %d, b = %d\n", a, b);
    }

    return 0;
}