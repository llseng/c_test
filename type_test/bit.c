/*
* @Author: llseng
* @Date:   2020-06-22 14:56:29
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-23 18:49:09
*/

#include <stdio.h>
#include <stdlib.h>

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

    printf("int sizeof%u\n", sizeof( int ) );
    printf("long sizeof%u\n", sizeof( long ) );
    printf("long long sizeof %u\n", sizeof( long long ) );
    printf("long double sizeof %u\n", sizeof( long double ) );

    char num_size;
    unsigned long long num = 1;

    num_size = sizeof( num ) * 8;

    printf("num_len = %u\n", sizeof( num ) );

    for (i = 0; i < num_size; ++i)
    {
        printf("num << %d = %llu\n", i, num << i);
    }

    return 0;
}