#ifndef __ARRAY_STACK_H__
#define __ARRAY_STACK_H__

#define MAX_ARRAY_STACK_SIZE 10

typedef struct array_stack
{
    int data[ MAX_ARRAY_STACK_SIZE ];
    int top;
} ArrayStack;

void init_array_stack( ArrayStack *stack );
int empty_array_stack( ArrayStack *stack );
int full_array_stack( ArrayStack *stack );
int pop_array_stack( ArrayStack *stack, int i );
int push_array_stack( ArrayStack *stack );
int top_array_stack( ArrayStack *stack, int *i );

#endif /* __ARRAY_STACK_H__ */