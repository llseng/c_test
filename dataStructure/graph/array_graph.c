#include <stdio.h>
#include "array_graph.h"
#include "../linearTable/linear_queue.h"

void init_array_graph( AG G )
{
    int i, j;
    G->directed = 0;
    G->vertex_len = 0;
    for ( i = 0; i < VERTEX_MAX; i++)
    {
        for ( j = 0; j < VERTEX_MAX; j++)
        {
            G->matrix[ i ][ j ] = DEF_ARC_VALUE;
        }
        
    }
    
    return ;
}

int full_array_graph( AG G )
{
    if( G->vertex_len < VERTEX_MAX ) return 0;
    return 1;
}

int empty_array_graph( AG G )
{
    if( G->vertex_len == 0 ) return 1;
    return 0;
}

int get_vex_array_graph( AG G, vertex_type v )
{
    if( empty_array_graph( G ) ) return 0;
    int res = 0, i;
    for ( i = 0; i < G->vertex_len; i++)
    {
        if( v == G->vertex[ i ] )
        {
            res = i + 1;
            break;
        }
    }
    
    return res;
}

int get_arc_array_graph( AG G, vertex_type v, vertex_type w )
{
    if( empty_array_graph( G ) ) return 0;
    int vk, wk;
    vk = get_vex_array_graph( G, v );
    if( !vk ) return 0;
    wk = get_vex_array_graph( G, w );
    if( !wk ) return 0;
    if( vk == wk ) return 0;

    if( G->matrix[ vk -1 ][ wk -1 ] == DEF_ARC_VALUE ) return 0;
    return 1;
}

int first_vex_array_graph( AG G, vertex_type v, vertex_type *dest )
{
    if( empty_array_graph( G ) || G->vertex_len < 2 ) return 0;
    int vk, i, res = 0;
    vk = get_vex_array_graph( G, v );
    if( !vk ) return 0;
    for ( i = 0; i < G->vertex_len; i++)
    {
        if( G->matrix[ vk - 1 ][ i ] != DEF_ARC_VALUE )
        {
            *dest = G->vertex[ i ];
            res = 1;
            break;
        }
    }
    
    return res;
}

int next_vex_array_graph( AG G, vertex_type v, vertex_type w, vertex_type *dest )
{
    if( empty_array_graph( G ) || G->vertex_len < 2 ) return 0;
    int vk, wk, i, res = 0;
    vk = get_vex_array_graph( G, v );
    if( !vk ) return 0;
    wk = get_vex_array_graph( G, w );
    if( !wk ) return 0;
    if( vk == wk ) return 0;
    if( G->matrix[ vk - 1 ][ wk - 1 ] == DEF_ARC_VALUE ) return 0;
    
    for ( i = wk; i < G->vertex_len; i++)
    {
        if( G->matrix[ vk - 1 ][ i ] != DEF_ARC_VALUE )
        {
            *dest = G->vertex[ i ];
            res = 1;
            break;
        }
    }
    
    return res;
}

int insert_vex_array_graph( AG G, vertex_type v )
{
    if( full_array_graph( G ) ) return 0;
    G->vertex[ G->vertex_len++ ] = v;
    return 1;
}

int insert_arc_array_graph( AG G, vertex_type v, vertex_type w )
{
    if( empty_array_graph( G ) || G->vertex_len < 2 ) return 0;
    int vk, wk, i, res = 0;
    vk = get_vex_array_graph( G, v );
    if( !vk ) return 0;
    wk = get_vex_array_graph( G, w );
    if( !wk ) return 0;
    if( vk == wk ) return 0;
    
    G->matrix[ vk - 1 ][ wk - 1 ] = 0;

    if( !G->directed )
    {
        G->matrix[ wk - 1 ][ vk - 1 ] = 0;
    }

    return 1;
}

int delete_vex_array_graph( AG G, vertex_type v )
{
    if( empty_array_graph( G ) ) return 0;
    int vk, i, j;
    vk = get_vex_array_graph( G, v );
    if( !vk ) return 0;
    vk--;
    G->vertex_len--;

    for ( i = vk; i < G->vertex_len; i++)
    {
        G->vertex[ i ] = G->vertex[ i + 1 ];
    }

    for ( i = vk; i < G->vertex_len; i++)
    {
        for ( j = 0; j < G->vertex_len; j++)
        {
            if( j < vk )
            {
                G->matrix[ i ][ j ] = G->matrix[ i + 1 ][ j ];
                G->matrix[ j ][ i ] = G->matrix[ j ][ i + 1 ];
            }else{
                if( j < i ) continue;
                G->matrix[ i ][ j ] = G->matrix[ i + 1 ][ j + 1 ];
                G->matrix[ j ][ i ] = G->matrix[ j + 1 ][ i + 1 ];
            }
        }
        
    }
    
    return 1;
}

int delete_arc_array_graph( AG G, vertex_type v, vertex_type w )
{
    if( empty_array_graph( G ) || G->vertex_len < 2 ) return 0;
    int vk, wk, i, res = 0;
    vk = get_vex_array_graph( G, v );
    if( !vk ) return 0;
    wk = get_vex_array_graph( G, w );
    if( !wk ) return 0;
    if( vk == wk ) return 0;

    G->matrix[ vk - 1 ][ wk - 1 ] = DEF_ARC_VALUE;

    if( !G->directed )
    {
        G->matrix[ wk - 1 ][ vk - 1 ] = DEF_ARC_VALUE;
    }

    return 1;
}

int traverse_array_graph( AG G, int tag )
{
    if( empty_array_graph( G ) ) return 0;

    int tmp_vexs[ VERTEX_MAX ];
    int i, k, vexk, tmp_vexk = 0;
    int vex_exist;
    LinearQueue lqueue, *LQ;
    LQ = &lqueue;
    init_linear_queue( LQ );

    en_linear_queue( LQ, 0 );

    while ( tmp_vexk < G->vertex_len )
    {
        if( empty_linear_queue( LQ ) ) break;
        re_linear_queue( LQ, &vexk );
        de_linear_queue( LQ );
        tmp_vexs[ tmp_vexk++ ] = vexk;

        printf( "%c ", G->vertex[ vexk ] );

        for ( i = 0; i < G->vertex_len; i++)
        {
            if( G->matrix[ vexk ][ i ] > DEF_ARC_VALUE )
            {
                vex_exist = 0;
                for ( k = 0; k < tmp_vexk; k++)
                {
                    if( tmp_vexs[ k ] == i )
                    {
                        vex_exist = 1;
                        break;
                    }
                }
                
                if( !vex_exist )
                {
                    en_linear_queue( LQ, i );
                }
            }
        }
        
    }
    
    printf( "\n" );

    return 1;
}