#include <stdio.h>
#include <time.h>

#define TIME 1000000000
int m, n = TIME; /* 全局变量 */

int main(void)
{   
    time_t start, stop;
    register int a, b = TIME; /* 寄存器变量 */
    int x, y = TIME;          /* 一般变量   */

    time(&start);
    for (a = 0; a < b; a++);
    time(&stop);
    printf("寄存器变量用时: %ld 秒\n", stop - start);
    
    time(&start);
    for (x = 0; x < y; x++);
    time(&stop);
    printf("一般变量用时: %ld 秒\n", stop - start);
    
    time(&start);
    for (m = 0; m < n; m++);
    time(&stop);
    printf("全局变量用时: %ld 秒\n", stop - start);

    return 0;
}