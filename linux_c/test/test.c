/*
* @Author: llseng
* @Date:   2020-06-28 11:27:04
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-28 11:29:49
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    printf("WNOHANG : %d\n", WNOHANG);
    return 0;
}