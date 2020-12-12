/*
* @Author: llseng
* @Date:   2020-06-04 17:51:16
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-04 19:29:41
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 9710
#define MAX_LINE 255

extern int errno;

void error_exit( char * );

int main( int argc, char const *argv[] ) {

    printf("argc %d\n", argc);
    printf("argv[0] %s\n", argv[0]);

    struct sockaddr_in socket_addr;
    int socket_fd, socket_domain, socket_type, socket_addr_len;
    int connect_status, recv_len, send_len;
    char recv_buf[ MAX_LINE ], send_buf[ MAX_LINE ];

    socket_domain = AF_INET;
    socket_type = SOCK_STREAM;
    socket_addr_len = sizeof( socket_addr );
    // 建立socket通信
    socket_fd = socket( socket_domain, socket_type, 0 );
    if( socket_fd < 0 ) {
        error_exit( "socket" );
    }
    // 置0
    memset( &socket_addr, 0, socket_addr_len );
    socket_addr.sin_family = socket_domain;
    socket_addr.sin_port = htons( SERVER_PORT );
    socket_addr.sin_addr.s_addr = inet_addr( SERVER_ADDR );
    // 建立socket连线
    connect_status = connect( socket_fd, (struct sockaddr *)&socket_addr, socket_addr_len );
    if( connect_status < 0 ) {
        error_exit( "connect" );
    }
    printf( "socket_fd %d connect to %s at PROT %d\n", socket_fd, inet_ntoa( socket_addr.sin_addr ), ntohs( socket_addr.sin_port ) );

    printf("connect success...\n");

    if( argc > 1 ) 
        strcpy( send_buf, argv[1] );
    else
        strcpy( send_buf, "Hello Server" );
    send_buf[ strlen( send_buf ) ] = '\n';


    // 发送数据
    send_len = send( socket_fd, send_buf, strlen( send_buf ), 0 );
    if( send_len < 0 ) {
        close( socket_fd );
        error_exit( "send" );
    }
    printf( "send_len %d, send_buf_len %d \nsend_buf\n>>>%s<<<\n", send_len, strlen( send_buf ), send_buf );

    // 读取数据
    recv_len = recv( socket_fd, recv_buf, MAX_LINE, 0 );
    if( recv_len <= 0 ) {
        close( socket_fd );
        error_exit( "recv" );
    }
    printf( "recv_len %d, recv_buf_len %d \nrecv_buf\n>>>%s<<<\n", recv_len, strlen( recv_buf ), recv_buf );

    // 关闭连接
    close( socket_fd );

    return 0;
}

void error_exit( char *str ) {
    fprintf(stderr, "%s ERROR: errno %d errstr %s\n", str, errno, strerror( errno ) );
    exit( errno );
}