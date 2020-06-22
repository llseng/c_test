/*
* @Author: llseng
* @Date:   2020-06-22 14:56:29
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-22 15:49:58
*/

#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a = 5, b = -5;
    int int_len = sizeof( int );
    int int_bit_len = int_len * 8;

    printf("a = %d, b = %d\n", a, b);
    printf("int_len = %d, int_bit_len = %d\n", int_len, int_bit_len);

    unsigned int c = 0xFFFFFFFB;
    printf("c = %u\n", c >> 31);
    printf("c = %d\n", c >> 31);

    char d[] = "test";
    printf("d len = %d\n", sizeof( d ) );

    int i;
    for (i = 0; i < sizeof( d ); ++i)
    {
        printf("d[%d] = %d\n", i, d[i]);
    }

    printf("d = %x\n", d );

    return 0;
}