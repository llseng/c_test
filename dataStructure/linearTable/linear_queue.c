#include <stdlib.h>
#include <string.h>
#include "linear_queue.h"

LinearQueueNode *linear_queue_node_malloc( void )
{
    LinearQueueNode *node = (LinearQueueNode *)malloc( sizeof( LinearQueueNode ) );
    memset( node, 0, sizeof( LinearQueueNode ) );
    node->next = NULL;
    return node;
}

void init_linear_queue( LQ q )
{
    q->head = q->tail = linear_queue_node_malloc();
}

int empty_linear_queue( LQ q )
{
    if( q->head == q->tail ) return 1;
    return 0;
}

int full_linear_queue( LQ q )
{
    return 0;
}

int en_linear_queue( LQ q, int i )
{
    if( full_linear_queue( q ) ) return 0;
    LinearQueueNode *new_node = linear_queue_node_malloc();
    new_node->data = i;
    q->tail->next = new_node;
    q->tail = new_node;
    return 1;
}

int de_linear_queue( LQ q )
{
    if( empty_linear_queue( q ) ) return 0;
    LinearQueueNode *node = q->head->next;
    q->head->next = node->next;
    if( q->tail == node ) q->tail = q->head;
    free( node );
    return 1;
}

int re_linear_queue( LQ q, int *i )
{
    if( empty_linear_queue( q ) ) return 0;
    *i = q->head->next->data;
    return 1;
}