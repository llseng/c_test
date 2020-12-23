#ifndef __LINEAR_STACK_H__
#define __LINEAR_STACK_H__

typedef struct linear_stack_node
{
    int data;
    struct linear_stack_node *next;
} LinearStackNode, *LinearStack;

LinearStack init_linear_stack( );
int empty_linear_stack( LinearStack stack );
int full_linear_stack( LinearStack stack );
int pop_linear_stack( LinearStack stack, int i );
int push_linear_stack( LinearStack stack );
int top_linear_stack( LinearStack stack, int *i );

#endif /* __LINEAR_STACK_H__ */