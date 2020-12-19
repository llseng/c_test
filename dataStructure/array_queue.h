#ifndef __ARRAY_QUEUE_H__
#define __ARRAY_QUEUE_H__
/**
 * 数组循环队列 
 */
#define MAX_ARRAY_QUEUE_SIZE 10

typedef struct array_queue
{
    int data[ MAX_ARRAY_QUEUE_SIZE ];
    int head, tail;
} ArrayQueue;

void init_array_queue( ArrayQueue *q );
int empty_array_queue( ArrayQueue *q );
int full_array_queue( ArrayQueue *q );
int en_array_queue( ArrayQueue *q, int i );
int de_array_queue( ArrayQueue *q );
int re_array_queue( ArrayQueue *q, int *i );

#endif /* __ARRAY_QUEUE_H__ */