/*
* @Author: llseng
* @Date:   2020-06-18 11:58:56
* @Last Modified by:   llseng
* @Last Modified time: 2020-07-01 11:54:10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*书属性*/
struct book_attr {
    int line; //页数
    char title[ 20 ]; //标题
    char author[ 20 ]; //作者
    char intro[ 100 ]; //介绍
};
typedef struct book_attr book_attr_t;

static book_attr_t bal[ 10 ], ba, *bal_p, *ba_p;

int main(int argc, char const *argv[])
{

    bal_p = bal;
    ba_p = &ba;

    printf("bal sizeof = %u\n", sizeof( bal ) ); //bal sizeof = 1440
    printf("ba sizeof = %u\n", sizeof( ba ) ); //ba sizeof = 144
    printf("bal_p sizeof = %u\n", sizeof( bal_p ) ); //bal_p sizeof = 8
    printf("ba_p sizeof = %u\n", sizeof( ba_p ) ); //ba_p sizeof = 8
    printf("*bal_p sizeof = %u\n", sizeof( *bal_p ) ); //*bal_p sizeof = 144
    printf("*ba_p sizeof = %u\n", sizeof( *ba_p ) ); //*ba_p sizeof = 144

    return 0;
}
