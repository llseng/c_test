/*
 * @Author: llseng 
 * @Date: 2020-07-20 15:08:15 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-21 16:06:11
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "text.h"

int text_input( void *data, unsigned int len ) {
    char *pos;
    pos = memchr( data, TEXT_DELIMITER, len );
    if( pos == NULL ) {
        return 0;
    }

    return abs( pos - (char *)data ) + 1;
}

int text_encode( void *code, unsigned int len, void *dest ) {
    memmove( dest, code, len );
    printf( "dest |%s|\n", dest);
    memset( (dest + len ), TEXT_DELIMITER, 1 );
    memset( (dest + len + 1), 0, 1 );
    printf( "dest |%s|\n", dest);
    return 0;
}

int text_decode( void *data, unsigned int len, void *dest ) {
    int length;
    length = text_input( data, len );
    if( length == 0 ) {
        memmove( dest, data, len );
    }else{
        memmove( dest, data, length - 1 );
    }
    printf( "text_decode dest |%s|\n", dest );
    return 0;
}

int text_send( tcp_text_t *s, void *data, unsigned int len ) {
    int buf_len = len < MAX_MESSAGE_SIZE? len + 2: MAX_MESSAGE_SIZE - 1;
    char buf[ buf_len ];
    memset( buf, 0, buf_len );
    text_encode( data, buf_len - 2, buf );
    printf( "send buf |%s|\n", buf );
    return send( s->sock, buf, buf_len, 0 );
}

int text_read( tcp_text_t *s, void *data ) {
    char buf[ MAX_MESSAGE_LINE ];
    int length = 0, buf_len, r_len;
    buf_len = s->buf_end - s->buf_last;
    printf( "1\n" );
    do{
        memset(buf, 0, MAX_MESSAGE_LINE);
        int read_len = buf_len < MAX_MESSAGE_LINE? buf_len: MAX_MESSAGE_LINE;
        r_len = recv( s->sock, buf, read_len, 0 );
        printf( "r_len %d\n", r_len);
        printf( "buf |%s|\n", buf);
        if( r_len < 1 ) return -1;
        length = text_input( buf, r_len );
        printf( "length %d\n", length);
        if( length == 0 ) {
            memcpy( s->buf_last, buf, r_len );
            buf_len -= r_len;
            s->buf_last += r_len;
        }else{
            memcpy( s->buf_last, buf, length );
            buf_len -= length;
            s->buf_last += length;
        }
        printf( "buf_len %d\n", buf_len);
        printf( "buf_last %p\n", s->buf_last);
    }while ( buf_len < 1 || length == 0 );
    printf( "2\n" );
    
    printf( "s->buf |%s|\n", s->buf);
    int data_len = s->buf_last - s->buf;
    printf( "data_len %d\n", data_len);
    text_decode( s->buf, data_len, data );
    printf( "data |%s|\n", data);
    printf( "data %p\n", data);
    printf( "3\n" );

    s->buf_last = s->buf;
    memset( s->buf_last, 0, MAX_MESSAGE_SIZE );
    if( length ) {
        int last_len = r_len - length;
        printf( "last_len %d\n", last_len);
        memcpy( s->buf_last, buf + length, last_len );
        s->buf_last += last_len;
    }
    printf( "4\n" );
        
    printf( "buf_last %p\n", s->buf_last);

    return data_len;
}