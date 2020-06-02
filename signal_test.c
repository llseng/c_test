/*
* @Author: llseng
* @Date:   2020-06-02 12:10:42
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-02 14:34:26
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <windows.h>

/**
 * @author llseng
 * @date   2020-06-02
 * @mail   1300904522@qq.com
 * @link   https://www.whymust.xyz
 * @param  int                     信号
 * 信号处理函数
 */
void sighandler( int );

int main( int argc, char const *argv[] ) {
    signal( SIGABRT, sighandler );
    signal( SIGFPE, sighandler );
    signal( SIGILL, sighandler );
    signal( SIGINT, sighandler );
    signal( SIGSEGV, sighandler );
    signal( SIGTERM, sighandler );

    unsigned int num = 5;

    while( num-- ) {
        // fflush( stdin );
        // system( "cls" );
        // printf("num = %d, sleep 1 second...\n", num);
        fprintf(stdout ,"num = %d, sleep 1 second...\n", num);
        fflush( stdout );
        sleep( 1 );
    }

    // abort();

    return 0;

}

void sighandler( int signum ) {
    switch( signum ) {
        case SIGABRT :
            // printf("(Signal Abort) 程序异常终止。\n");
            fputs("(Signal Abort) 程序异常终止。\n", stdout);
            break;

        case SIGFPE :
            // printf("(Signal Floating-Point Exception) 算术运算出错，如除数为 0 或溢出（不一定是浮点运算）。\n");
            fputs("(Signal Floating-Point Exception) 算术运算出错，如除数为 0 或溢出（不一定是浮点运算）。\n", stdout);
            break;

        case SIGILL :
            // printf("(Signal Illegal Instruction) 非法函数映象，如非法指令，通常是由于代码中的某个变体或者尝试执行数据导致的。\n");
            fputs("(Signal Illegal Instruction) 非法函数映象，如非法指令，通常是由于代码中的某个变体或者尝试执行数据导致的。\n", stdout);
            break;
        
        case SIGINT :
            // printf("(Signal Interrupt) 中断信号，如 ctrl-C，通常由用户生成。\n");
            puts("(Signal Interrupt) 中断信号，如 ctrl-C，通常由用户生成。\n");
            break;
        
        case SIGSEGV :
            // printf("(Signal Segmentation Violation) 非法访问存储器，如访问不存在的内存单元。\n");
            fputs("(Signal Segmentation Violation) 非法访问存储器，如访问不存在的内存单元。\n", stdout);
            break;
        
        case SIGTERM :
            // printf("(Signal Terminate) 发送给本程序的终止请求信号。\n");
            fputs("(Signal Terminate) 发送给本程序的终止请求信号。\n", stdout);
            break;

        default :
            // printf("其他信号。\n");
            fputs("其他信号。\n", stdout);
    }

    exit( 0 );
}