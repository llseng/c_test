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
    memset( (dest + len ), TEXT_DELIMITER, 1 );
    memset( (dest + len + 1), 0, 1 );
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
    
    return 0;
}

int text_send( tcp_text_t *s, void *data, unsigned int len ) {
    int buf_len = len < MAX_MESSAGE_SIZE? len + 2: MAX_MESSAGE_SIZE - 1;
    char buf[ buf_len ];
    memset( buf, 0, buf_len );
    text_encode( data, buf_len - 2, buf );
    
    return send( s->sock, buf, buf_len, 0 );
}

int text_read( tcp_text_t *s, void *data ) {
    char buf[ MAX_MESSAGE_LINE ];
    int length = 0, buf_len, r_len, data_len;
    buf_len = s->buf_end - s->buf_last;
    data_len = s->buf_last - s->buf;

    length = text_input( s->buf, data_len );
    while( buf_len && length == 0 ){
        memset(buf, 0, MAX_MESSAGE_LINE);
        int read_len = buf_len < MAX_MESSAGE_LINE? buf_len: MAX_MESSAGE_LINE;
        r_len = recv( s->sock, buf, read_len, 0 );
        if( r_len < 1 ) return -1;
        
        memmove( s->buf_last, buf, r_len );
        buf_len -= r_len;
        s->buf_last += r_len;
        data_len += r_len;

        length = text_input( s->buf, data_len );
    }

    if( buf_len == 0 && length == 0 ) {
        length = data_len;
    }

    text_decode( s->buf, length, data );

    int last_len = data_len - length;

    if( last_len ) {
        memmove( s->buf, s->buf + length, last_len );
    }

    s->buf_last = s->buf + last_len;
    memset( s->buf_last, 0, length );

    return data_len;
}