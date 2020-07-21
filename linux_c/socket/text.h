/*
 * @Author: llseng 
 * @Date: 2020-07-20 14:33:56 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-21 14:46:44
 */

#ifndef _TEXT_H_
#define _TEXT_H_

#ifdef linux

#include <sys/socket.h>

#else /*linux*/

#define AF_INET 1;
#define SOCK_STREAM 1;
struct in_addr {
    int s_addr;
};
struct sockaddr_in {
    int sin_family;
    int sin_port;
    struct in_addr sin_addr;
};

#endif /*linux*/

#define TEXT_DELIMITER '\n'
#define MAX_MESSAGE_SIZE 1024
#define MAX_MESSAGE_LINE 128

typedef struct tcp_text {
    int sock;
    struct sockaddr_in addr;
    char buf[ MAX_MESSAGE_SIZE ];
    char *buf_last;
    char *buf_end;
} tcp_text_t;

int text_input( void *data, unsigned int len );

int text_encode( void *code, unsigned int len, void *data );

int text_decode( void *data, unsigned int len, void *code );

int text_send( tcp_text_t *s, void *data, unsigned int len );

int text_read( tcp_text_t *s, void *data );

#define text_recv( s, data, len ) text_read( s, data, len )

#endif /* _TEXT_H_ */