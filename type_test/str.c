/*
* @Author: llseng
* @Date:   2020-06-17 19:15:27
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-17 19:23:01
*/

#include <stdio.h>
#include <string.h>

struct m_t {
    int a;
    char b;
    char c[10];
};

int main() {

    struct m_t a = { 1, '1', "123456" };

    printf("%d %d\n", sizeof( a ), sizeof( a.c ) );

    return 0;
}