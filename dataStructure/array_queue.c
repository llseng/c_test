#include <stdio.h>
#include "array_queue.h"

void init_array_queue( ArrayQueue *q )
{
    q->head = q->tail = 0;
}

int empty_array_queue( ArrayQueue *q )
{
    if( q->head % MAX_ARRAY_QUEUE_SIZE == q->tail % MAX_ARRAY_QUEUE_SIZE ) return 1;
    return 0;
}

int full_array_queue( ArrayQueue *q )
{
    if( ( q->tail + 1 ) % MAX_ARRAY_QUEUE_SIZE == q->head % MAX_ARRAY_QUEUE_SIZE ) return 1;
    return 0;
}

int en_array_queue( ArrayQueue *q, int i )
{
    if( full_array_queue( q ) ) return 0;
    q->data[ q->tail++ ] = i;
    return 1;
}

int de_array_queue( ArrayQueue *q )
{
    if( empty_array_queue( q ) ) return 0;
    q->head++;
    return 1;
}

int re_array_queue( ArrayQueue *q, int *i )
{
    if( empty_array_queue( q ) ) return 0;
    *i = q->data[ q->head ];
    return 1;
}
