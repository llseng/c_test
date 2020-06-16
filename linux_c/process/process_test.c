/*
* @Author: llseng
* @Date:   2020-06-16 11:55:09
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-16 17:09:31
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

extern int errno;

void error_exit( char *str ) {
    fprintf(stderr, "%s ERROR: errno %d errstr %s\n", str, errno, strerror( errno ) );
    exit( errno );
}

int main( int argc, const char *argv[] ) {

    pid_t pid;

    pid = fork();
    if( pid < 0 ) {
        error_exit( "fork" );
    }

    if( pid ) {
        printf("this is parent;\n");
        sleep( 10 ); // 睡眠10s, 等待子进程先退出
    }else{
        printf("this is child\n");
        exit( 1 ); // 子进程退出, 父进程未回收导致子进程变成僵尸进程
        // sleep( 10 );
    }

    system("ps -o pid,ppid,state,tty,command");
    printf("pid %d ppid %d end\n", getpid(), getppid());

    return 0;
}