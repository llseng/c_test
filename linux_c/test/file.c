/*
 * @Author: llseng 
 * @Date: 2020-07-09 11:30:03 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-09 15:59:44
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

    FILE * logfd = NULL;
    long log_size;
    char log_file[] = "../../test.txt", *cres,*buf, strbuf[1024];
    int res, i;
    book_attr_t ba, bal[3], ba_buf;

    printf( "log_file = '%s' __FILE__ = '%s' __LINE__ = %d\n", log_file, __FILE__, __LINE__ );

    logfd = fopen( log_file, "wb+" );
    if( logfd == NULL ) {
        perror( "fopen" );
        return 0;
    }

    ba.line = 516;
    strcpy( ba.title, "书1" );
    strcpy( ba.author, "lls" );
    strcpy( ba.intro, "书1书1书1书1书1书1书1" );

    for ( i = 0; i < 3; i++)
    {
        bal[i].line = 52 * i;
        sprintf( strbuf, "书书%d", i);
        strcpy( bal[i].title, strbuf );
        strcpy( bal[i].author, "lls" );
        sprintf( strbuf, "书%d书%d书%d", i, i, i);
        strcpy( bal[i].intro, strbuf );
    }

    res = fwrite( (void *)&ba, sizeof( ba ), 1, logfd );
    if( res < 1 ) {
        perror( "fwrite" );
        return 0;
    }

    res = ftell( logfd );
    printf( "ftell res = %ld\n", res );
    
    res = fwrite( (void *)bal, sizeof( bal[0] ), 3, logfd );
    if( res < 1 ) {
        perror( "fwrite" );
        return 0;
    }
    
    res = ftell( logfd );
    printf( "ftell res = %ld\n", res );

    /*文件指针回到头部*/
    res = fseek( logfd, 0, SEEK_SET);
    if( res != 0 ) {
        perror( "fseek" );
        return 0;
    }

    while ( feof( logfd ) == 0 )
    {
        printf( ">>>\n" );

        res = fread( &ba_buf, sizeof( book_attr_t ), 1, logfd );
        printf( "fread res = %d\n", res );
        if( res < 1 ) {
            perror( "fread" );
            // return 0;
            continue;
        }

        printf( "ba_buf.line = %d\n", ba_buf.line );
        printf( "ba_buf.title = %s\n", ba_buf.title );
        printf( "ba_buf.author = %s\n", ba_buf.author );
        printf( "ba_buf.intro = %s\n", ba_buf.intro );

        printf( "<<<\n" );
    }

    printf( "end\n" );
    
    res = ftell( logfd );
    printf( "ftell res = %ld\n", res );

    fclose( logfd );

    return 0;
}
