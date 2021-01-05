#include <stdio.h>
#include "array_graph.h"

void show_matrix( int M[ VERTEX_MAX ][ VERTEX_MAX ], int len );

int main(int argc, char const *argv[])
{
    int i, k, vexs[ 5 ] = {'A', 'B', 'C', 'D', 'E'};
    int arc[ 7 ][2] = {
        { 'A', 'B'},
        { 'A', 'C'},
        { 'A', 'E'},
        { 'B', 'D'},
        { 'C', 'D'},
        { 'C', 'E'},
        { 'D', 'E'},
    };
    ArrayGraph aGraph, *AG;
    AG = &aGraph;
    init_array_graph( AG );

    for ( i = 0; i < 5; i++)
    {
        insert_vex_array_graph( AG, vexs[ i ] );
    }

    for ( i = 0; i < 7; i++)
    {
        insert_arc_array_graph( AG, arc[ i ][ 0 ], arc[ i ][ 1 ] );
    }

    show_matrix( AG->matrix, AG->vertex_len );
    traverse_array_graph( AG, 1 );

    k = get_vex_array_graph( AG, 'H' );
    printf( "vex %c -> %d\n", 'H', k );

    for ( i = 0; i < 5; i++)
    {
        k = get_vex_array_graph( AG, vexs[ i ] );
        printf( "vex %c -> %d\n", vexs[ i ], k );
    }

    k = get_arc_array_graph( AG, 'A','D' );
    printf( "vex %c %c -> %d\n", 'A', 'D', k );

    for ( i = 0; i < 7; i++)
    {
        k = get_arc_array_graph( AG, arc[ i ][ 0 ], arc[ i ][ 1 ] );
        printf( "vex %c %c -> %d\n", arc[ i ][ 0 ], arc[ i ][ 1 ], k );
    }

    first_vex_array_graph( AG, 'A', &k );
    printf( "first A %c\n", k );
    next_vex_array_graph( AG, 'A', k, &k );
    printf( "next %c\n", k );

    delete_arc_array_graph( AG, 'A', 'E' );
    printf( "delete arc A E\n" );
    show_matrix( AG->matrix, AG->vertex_len );

    delete_vex_array_graph( AG, 'C' );
    printf( "delete vex C\n" );
    show_matrix( AG->matrix, AG->vertex_len );

    return 0;
}

void show_matrix( int M[ VERTEX_MAX ][ VERTEX_MAX ], int len )
{
    int i, j;

    printf("----------\n");

    for ( i = 0; i < len; i++)
    {
        for ( j = 0; j < len; j++)
        {
            printf("%d  ", M[ i ][ j ]);
        }
        printf("\n");
    }
    
    printf("\n");

    return ;
}