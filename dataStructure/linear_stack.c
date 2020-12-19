#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linear_stack.h"

LinearStackNode *linear_stack_node_malloc( void )
{
    LinearStackNode * node = (LinearStackNode *)malloc( sizeof( LinearStackNode ) );
    memset( node, 0, sizeof( LinearStackNode ) );
    node->next = NULL;
    return node;
}

LinearStack init_linear_stack( )
{
    LinearStackNode * head = linear_stack_node_malloc();
    return head;
}

int empty_linear_stack( LinearStack stack )
{
    if( stack->next == NULL ) return 1;
    return 0;
}

int full_linear_stack( LinearStack stack )
{
    return 0;
}

int pop_linear_stack( LinearStack stack, int i )
{
    if( full_linear_stack( stack ) ) return 0;
    LinearStackNode * new_node = linear_stack_node_malloc();
    new_node->data = i;
    new_node->next = stack->next;
    stack->next = new_node;
    return 1;
}

int push_linear_stack( LinearStack stack )
{
    if( empty_linear_stack( stack ) ) return 0;
    LinearStackNode *node = stack->next;
    stack->next = node->next;
    free( node );
    return 1;
}

int top_linear_stack( LinearStack stack, int *i )
{
    if( empty_linear_stack( stack ) ) return 0;
    *i = stack->next->data;
    return 1;
}
