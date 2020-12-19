#include <stdlib.h>
#include "array_stack.h"

void init_array_stack( ArrayStack *stack )
{
    stack->top = 0;
}

int empty_array_stack( ArrayStack *stack )
{
    if( stack->top == 0 ) return 1;
    return 0;
}

int full_array_stack( ArrayStack *stack )
{
    if( stack->top == MAX_ARRAY_STACK_SIZE ) return 1;
    return 0;
}

int pop_array_stack( ArrayStack *stack, int i )
{
    if( full_array_stack( stack ) ) return 0;
    stack->top++;
    stack->data[ stack->top ] = i;
    return 1;
}

int push_array_stack( ArrayStack *stack )
{
    if( empty_array_stack( stack ) ) return 0;
    stack->top--;
    return 1;
}

int top_array_stack( ArrayStack *stack, int *i )
{
    if( empty_array_stack( stack ) ) return 0;
    *i = stack->data[ stack->top ];
    return 1;
}
