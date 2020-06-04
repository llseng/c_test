/*
* @Author: llseng
* @Date:   2020-06-03 16:05:10
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-04 14:59:28
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// 同时能处理的最大连接数
#define MAX_BACKLOG 10
// 读取最大长度
#define MAX_LINE 255
// 监听端口
#define LISTEN_PORT 9710
// 监听地址
#define LISTEN_ADDR "127.0.0.1"

int main( int argc, char const *argv[] ) {

    struct sockaddr_in listen_addr, client_addr;
    int socket_fd, client_fd;
    int socket_domain, socket_type;
    int bind_status, listen_status, close_status;
    int client_addr_len, w_count, recv_len, send_len;
    int recv_buf[MAX_LINE];

    socket_domain = AF_INET;
    socket_type = SOCK_STREAM;
    // 创建socket通信
    socket_fd = socket( socket_domain, socket_type, 0 );
    if( socket_fd < 0 ) {
        perror( "socket" );
        exit( 1 );
    }
    // 内存置零
    bzero( &listen_addr, sizeof( listen_addr ) );
    listen_addr.sin_family = socket_domain;
    listen_addr.sin_port = htons( LISTEN_PORT );
    listen_addr.sin_addr.s_addr = inet_addr( LISTEN_ADDR );
    // 对shocket定位;绑定地址与端口
    bind_status = bind( socket_fd, &listen_addr, sizeof( listen_addr ) );
    if( bind_status < 0 ) {
        perror( "bind" );
        exit( 1 );
    }
    // 等待连接;设置监听
    listen_status = listen( socket_fd, MAX_BACKLOG );
    if( listen_status < 0 ) {
        perror( "listen" );
        exit( 1 );
    }

    printf("Accepting connections...\n");

    w_count = 10;
    while( w_count-- > 0 ) {

        client_addr_len = sizeof( client_addr );
        // 接受socket连接
        client_fd = accept( socket_fd, (struct sockaddr *)&client_addr, &client_addr_len );
        if( client_fd < 0 ) {
            perror( "accept" );
            continue;
            // exit( 1 );
        }

        printf( "client_fd %d connection from %s at PROT %d\n", client_fd, inet_ntoa( client_addr.sin_addr ), ntohs( client_addr.sin_port ) );

        bzero( recv_buf, sizeof( recv_buf ) );
        // 经socket接收数据
        recv_len = recv( client_fd, recv_buf, MAX_LINE, 0 );
        if( recv_len <= 0 ) {
            perror( "recv" );
            continue;
            // exit( 1 );
        }
        printf( "recv_len %d, recv_buf_len %d, recv_buf %s\n", recv_len, strlen( recv_buf ), recv_buf );

        // 经socket传送数据
        // send_len = send( client_fd, recv_buf, sizeof( recv_buf ), 0 );
        send_len = send( client_fd, recv_buf, recv_len, 0 );
        if( send_len < 0 ) {
            perror( "send" );
            continue;
            // exit( 1 );
        }
        printf( "send_len %d, send_buf_len %d, send_buf %s\n", send_len, strlen( recv_buf ), recv_buf );

        printf( "close client %d\n", client_fd );
        // 关闭文件;关闭客户端连接
        close_status = close( client_fd );
        if( close_status < 0 ) {
            perror( "close" );
            continue;
            // exit( 1 );
        }
    }

    printf( "close server %d\n", socket_fd );
    // 关闭文件;关闭客户端连接
    close_status = close( socket_fd );
    if( close_status < 0 ) {
        perror( "close" );
        exit( 1 );
    }

    return 0;
}