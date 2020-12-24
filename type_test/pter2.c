#include <stdio.h>

int main(int argc, char const *argv[])
{
    int s, *p = NULL;

    if( p ) printf( " p = NULL true\n");

    s = 0;
    p = &s;

    if( p ) printf( " p != NULL true\n");

    printf( "%d\n", s );

    return 0;
}
