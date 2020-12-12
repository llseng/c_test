/**
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "queue.h"

void MQ_init( MQ_link *link ) {
    MQ_node *start_node = MQ_be_node( NULL );
    // link->head = link->tail = start_node;
    link->head = start_node;
    link->tail = start_node;
    link->size = 0;
}

MQ_node *MQ_be_node( MQ_data value ) {
    MQ_node *new_node = (MQ_node *)malloc( sizeof( MQ_node ) );

    // size_t value_len = strlen( value );
    // MQ_data data = (MQ_data)malloc( (value_len + 1) * sizeof( MQ_data ) );
    new_node->data = value;
    new_node->next = NULL;

    return new_node;
}

int MQ_en( MQ_link *link, MQ_data value ) {
    MQ_node *new_node = MQ_be_node( value );
    link->tail->next = new_node;
    link->tail = new_node;
    link->size++;

    return TRUE;
}

int MQ_de( MQ_link *link, MQ_data *value ) {
    if( link->head == link->tail ) {
        *value = NULL;
        return FALSE;
    }

    MQ_node * temp_node = link->head->next;
    link->head->next = temp_node->next;
    link->size--;

    *value = temp_node->data;

    if( link->head->next == NULL ) {
        link->tail = link->head;
    }

    free( temp_node );

    return TRUE;
}