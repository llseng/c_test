#include "linear_list.h"
#include "linear_list.c"

void show_node( LinearNode * );
void show_list( LinearList );

int main(int argc, char const *argv[])
{
    LinearList list = init_linear_list();
    LinearNode *ln;
    LinearData ld;
    char s[20];
    int i, insert_s ;

    printf("len = %d\n", length_linear_list( list ));

    for ( i = 0; i < 10; i++)
    {
        ld.id = i;
        sprintf( s, "name%d", i );
        strcpy( ld.name, s );
        ld.age = i * 5;
        ld.sex = i % 2;
        ld.score = i * 66;
        
        printf("len = %d\n", length_linear_list( list ));
        insert_s = insert_linear_list( list, ld, length_linear_list( list ) + 1 );
        printf( "insert_s = %d\n", insert_s );
    }

    printf("len = %d\n", length_linear_list( list ));
    show_list( list );

    printf( "del staus 2 %d\n", delete_linear_list( list, 2 ) );

    printf( "del staus 20 %d\n", delete_linear_list( list, 20 ) );
    
    printf("len = %d\n", length_linear_list( list ));
    show_list( list );

    printf( "get 2\n");
    ln = get_linear_list( list, 2 );
    show_node( ln );

    printf( "get 20\n");
    ln = get_linear_list( list, 20 );
    show_node( ln );

    printf( "locate ld\n");
    ln = locate_linear_list( list, ld );
    show_node( ln );

    return 0;
}

void show_list( LinearList l )
{
    LinearNode *p = l;
    while ( p->next != NULL )
    {
        p = p->next;
        show_node( p );

    }
    
    return;
}

void show_node( LinearNode *d )
{
    if( d == NULL ) 
    {
        printf("node is NULL\n");
        return ;
    }
    printf( "id: %d, name: %s, age: %d, sex: %d, score: %d;\n", d->data.id, d->data.name, d->data.age, d->data.sex, d->data.score );
    return ;
}