/*
* @Author: llseng
* @Date:   2020-06-18 11:58:56
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-09 17:36:00
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

int main(int argc, char const *argv[])
{
    int i;
    book_attr_t a, b, c, **p;

    a.line = 1;
    strcpy( a.title, "a" );
    strcpy( a.author, "a" );
    strcpy( a.intro, "a" );

    b.line = 2;
    strcpy( b.title, "b" );
    strcpy( b.author, "b" );
    strcpy( b.intro, "b" );

    c.line = 3;
    strcpy( c.title, "c" );
    strcpy( c.author, "c" );
    strcpy( c.intro, "c" );

    p = (book_attr_t **)calloc( 1, sizeof( book_attr_t * ) );

    printf( "sizeof( p ) = %d\n", sizeof( p ) );
    printf( "sizeof( *p ) = %d\n", sizeof( *p ) );
    printf( "sizeof( **p ) = %d\n", sizeof( **p ) );

    printf( "p addr %p\n", &p );

    *(p+0) = &a;
    p = (book_attr_t **)realloc( p, 3 * sizeof( book_attr_t *) );
    *(p+1) = &b;
    *(p+2) = &c;

    printf( "a addr %p\n", &a );
    printf( "b addr %p\n", &b );
    printf( "c addr %p\n", &c );
    printf( "p addr %p\n", &p );
    
    for ( i = 0; i < 3; i++ )
    {
        printf( "addr %p\n", *(p +i) );

        printf( "p.line %d\n", (*(p +i))->line );
        printf( "p.title '%s'\n", (*(p +i))->title );
        printf( "p.author '%s'\n", (*(p +i))->author );
        printf( "p.intro '%s'\n", (*(p +i))->intro );
    }
    

    return 0;
}
