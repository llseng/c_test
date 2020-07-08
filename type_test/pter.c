/*
* @Author: llseng
* @Date:   2020-06-18 11:58:56
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-08 19:22:26
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

static void voidp_to_intp( void *p ) {
    // printf("p->author = %s\n", ((book_attr_t *)p)->author);
    printf("p = %d\n", *(int *)p );
}

static void *test_void( char* param ){
    printf( "param = %s\n", param );
}

int main(int argc, char const *argv[])
{

    bal_p = bal;
    ba_p = &ba;

    ba.line = 10;
    strcpy( ba.title, "test");
    strcpy( ba.author, "llseng");
    strcpy( ba.intro, "test,test,test");

    printf("bal sizeof = %u\n", sizeof( bal ) ); //bal sizeof = 1440
    printf("ba sizeof = %u\n", sizeof( ba ) ); //ba sizeof = 144
    printf("bal_p sizeof = %u\n", sizeof( bal_p ) ); //bal_p sizeof = 8
    printf("ba_p sizeof = %u\n", sizeof( ba_p ) ); //ba_p sizeof = 8
    printf("*bal_p sizeof = %u\n", sizeof( *bal_p ) ); //*bal_p sizeof = 144
    printf("*ba_p sizeof = %u\n", sizeof( *ba_p ) ); //*ba_p sizeof = 144

    int num = 123;

    // voidp_to_intp( (void *)&ba );
    voidp_to_intp( (void *)&num );

    void * ba_void_p;
    book_attr_t ba_void = {100, "test", "whymust", "test void *"};

    ba_void_p = &ba_void;

    void *(*f_1)(void *);
    f_1 = test_void;

    f_1( (void *)((book_attr_t *)ba_void_p)->intro );
    
    int ba_arr_len = 2;
    book_attr_t *ba_arr = (book_attr_t *)calloc( ba_arr_len, sizeof( book_attr_t ) );

    strcpy( ba_arr[0].title, "0" );
    strcpy( ba_arr[1].title, "1" );

    printf( "ba_arr->title %s\n", ba_arr[0].title );
    printf( "ba_arr->title %s\n", ba_arr[1].title );

    ba_arr[0] = ba;


    printf( "ba_arr->title %s\n", ba_arr[0].title );
    printf( "ba_arr->author %s\n", ba_arr[0].author );
    printf( "ba_arr->intro %s\n", ba_arr[0].intro );
    printf( "ba_arr->title %s\n", ba_arr[1].title );
    
    strcpy( ba.title, "test0");

    printf( "ba_arr->title %s\n", ba_arr[0].title );
    printf( "ba_arr->author %s\n", ba_arr[0].author );
    printf( "ba_arr->intro %s\n", ba_arr[0].intro );
    printf( "ba_arr->title %s\n", ba_arr[1].title );

    return 0;
}
