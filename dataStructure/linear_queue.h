#ifndef __LINEAR_QUEUE_H__
#define __LINEAR_QUEUE_H__

typedef struct linear_queue_node
{
    int data;
    struct linear_queue_node *next;
} LinearQueueNode;

typedef struct linear_queue
{
    LinearQueueNode *head, *tail;
} LinearQueue, *LQ;

void init_linear_queue( LQ q );
int empty_linear_queue( LQ q );
int full_linear_queue( LQ q );
int en_linear_queue( LQ q, int i );
int de_linear_queue( LQ q );
int re_linear_queue( LQ q, int *i );

#endif /* __LINEAR_QUEUE_H__ */