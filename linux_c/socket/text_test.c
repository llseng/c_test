/*
 * @Author: llseng 
 * @Date: 2020-07-21 11:51:27 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-21 16:11:14
 */

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#ifdef linux

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif /*linux*/
#include "text.c"

// 同时能处理的最大连接数
#define MAX_BACKLOG 10
// 读取最大长度
#define MAX_LINE 255
// 监听端口
#define LISTEN_PORT 9710
// 监听地址
#define LISTEN_ADDR "127.0.0.1"

extern int errno;

void sock_close( int sockfd ) {
    int status;
    printf( "close socket %d\n", sockfd );
    // 关闭文件;关闭socket连接
    status = close( sockfd );
    if( status < 0 ) {
        perror( "close" );
    }
}

int main(int argc, char const *argv[])
{
    tcp_text_t t1, client_t;
    int socket_domain, socket_type, status;

    socket_domain = AF_INET;
    socket_type = SOCK_STREAM;

    t1.sock = socket( socket_domain, socket_type, 0 );

    memset( &t1.addr, 0, sizeof( t1.addr ) );

    t1.addr.sin_family = socket_domain;
    t1.addr.sin_port = htons( LISTEN_PORT );
    t1.addr.sin_addr.s_addr = inet_addr( LISTEN_ADDR );

    // 对shocket定位;绑定地址与端口
    status = bind( t1.sock, (struct sockaddr *)&t1.addr, sizeof( t1.addr ) );
    if( status < 0 ) {
        perror( "bind" );
        exit( 1 );
    }
    // 等待连接;设置监听
    status = listen( t1.sock, MAX_BACKLOG );
    if( status < 0 ) {
        perror( "listen" );
        exit( 1 );
    }

    printf("Accepting connections...\n");

    int w_count = 10;
    while( w_count-- > 0 ) {

        client_t.buf_last = client_t.buf;
        client_t.buf_end = client_t.buf + MAX_MESSAGE_SIZE;

        int client_addr_len = sizeof( client_t.addr );
        // 接受socket连接
        client_t.sock = accept( t1.sock, (struct sockaddr *)&client_t.addr, &client_addr_len );

        if( client_t.sock < 0 ) {
            perror( "accept" );
            continue;
            // exit( 1 );
        }

        status = text_send( &client_t, "connect success", strlen("connect success") );
        if( status < 0 ) {
            perror( "text_send" );
            continue;
            // exit( 1 );
        }

        printf( "client_fd %d connection from %s at PROT %d\n", client_t.sock, inet_ntoa( client_t.addr.sin_addr ), ntohs( client_t.addr.sin_port ) );

        char *p = malloc( MAX_MESSAGE_SIZE * sizeof( char ) );

        while( 1 ) {
            memset( p, 0, MAX_MESSAGE_SIZE * sizeof( char ) );
            status = text_read( &client_t, (void *)p );
            printf( "text_read status %d\n", status );
            if( status <= 0 ) {
                perror( "text_read" );
                break;
                // exit( 1 );
            }
            // int i = 0;
            // for ( i = 0; i < status; i++)
            // {
            //     printf( "|%s|\n", (p + i) );
            // }
            // printf( "\n" );
            
            printf( "p %p\n", p);
            printf( "p_len %d p>>>%s<<<\n", status, p );
        }
        free( p );

        sock_close( client_t.sock );
        if( errno > 0 ) {
            continue;
        }
    }

    sock_close( t1.sock );

    return 0;
}