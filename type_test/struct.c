#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data
{
    int id;
    char name[10];
};

typedef struct
{
    char s[100];
} string;


int main(int argc, char const *argv[])
{
    struct data a, b, *p;

    p = (struct data *)malloc( sizeof( struct data ) );

    a.id = 100;
    strcpy( a.name, "测试" );

    printf( "a.id = %d;\na.name = %s\n", a.id, a.name);

    b = a;
    
    printf( "b.id = %d;\nb.name = %s\n", b.id, b.name);

    printf( "memcmp %d\n",memcmp( &a, &b, sizeof( struct data ) ) );

    if( memcmp( &a, &b, sizeof( struct data ) ) == 0 ) {
        printf( "a == b\n");
    }else{
        printf( "a != b\n");
    }

    *p = b;
    
    printf( "p.id = %d;\np.name = %s\n", p->id, p->name);
    return 0;
}
