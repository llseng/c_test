/*
* @Author: llseng
* @Date:   2020-06-02 12:28:31
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-24 17:03:26
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

    int num_l[] = {0,1,2,3,4,5,6,7,8,9};

    printf("*num_l = %d\n", *num_l = 5);
    *num_l = 0;
    printf("*num_l = %d\n", *num_l);

    for (i = 0; i < 10; i++)
    {
        printf("num_l[%d] = %d\n", i, num_l[i]);
    }

    return 0;
}