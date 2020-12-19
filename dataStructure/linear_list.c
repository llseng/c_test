#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linear_list.h"

LinearNode *linear_node_malloc( void ) 
{
    LinearNode * node = ( LinearNode * )malloc( sizeof( LinearNode ) );
    memset( node, 0, sizeof( LinearNode ) );
    node->next = NULL;
    return node;
}

LinearList init_linear_list( void )
{
    LinearList head = linear_node_malloc();
    return head;
}

int length_linear_list( LinearList list )
{
    int len = 0;
    LinearNode * p = list;
    while ( p->next != NULL ) 
    {
        p = p->next;
        len++;
    }
    return len;
}

int insert_linear_list( LinearList list, LinearData data, int i ) 
{
    int c = 1;
    LinearNode *p = list, *new_node;
    while ( p->next != NULL && c < i )
    {
        p = p->next;
        c++;
    }
    
    if( c != i ) return 0;

    new_node = linear_node_malloc();
    new_node->data = data;
    new_node->next = p->next;
    p->next = new_node;

    return 1;
}

int delete_linear_list( LinearList list, int i )
{
    int c = 1;
    LinearNode *p = list, *del_node;
    while ( p->next != NULL && c < i )
    {
        p = p->next;
        c++;
    }
    
    if( c != i ) return 0;
    
    del_node = p->next;
    
    if( del_node != NULL ) {
        p->next = del_node->next;
        free( del_node );
    }

    return 1;
}


LinearNode *get_linear_list( LinearList list, int i )
{
    int c = 0;
    LinearNode *p = list;
    while ( p->next != NULL && c < i )
    {
        p = p->next;
        c++;
    }

    if( c != i ) return NULL;

    return p;
}

LinearNode *locate_linear_list( LinearList list, LinearData data )
{
    int c = 0, res = 0;
    LinearNode *p = list;
    while ( !res && p->next != NULL )
    {
        p = p->next;
        c++;
        if( memcmp( &(p->data), &data, sizeof( LinearData ) ) == 0 ) res = c;
    }

    if( res ) return p;

    return NULL;
}