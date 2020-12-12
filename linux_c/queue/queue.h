/**
 * 
 */

#include "../types.h"

typedef void *MQ_data;

struct message_queue_node;

typedef struct message_queue_node {
    MQ_data *data;
    struct message_queue_node *next;
} MQ_node;

typedef struct message_queue_link {
    MQ_node *head, *tail;
    unsigned int size;
} MQ_link;

void MQ_init( MQ_link *link );

MQ_node *MQ_be_node( MQ_data value );

int MQ_en( MQ_link *link, MQ_data value );

int MQ_de( MQ_link *link, MQ_data *value );
