#ifndef __ARRAY_GRAPH_H__
#define __ARRAY_GRAPH_H__

#define VERTEX_MAX 10
#define DEF_ARC_VALUE -1

typedef int vertex_type;

typedef struct array_graph
{
    int directed;
    int vertex_len;
    vertex_type vertex[ VERTEX_MAX ];
    int matrix[ VERTEX_MAX ][ VERTEX_MAX ];
} ArrayGraph, *AG;

void init_array_graph( AG G );
int full_array_graph( AG G );
int empty_array_graph( AG G );
int get_vex_array_graph( AG G, vertex_type v );
int get_arc_array_graph( AG G, vertex_type v, vertex_type w );
int first_vex_array_graph( AG G, vertex_type v, vertex_type *dest );
int next_vex_array_graph( AG G, vertex_type v, vertex_type w, vertex_type *dest );
int insert_vex_array_graph( AG G, vertex_type v );
int insert_arc_array_graph( AG G, vertex_type v, vertex_type w );
int delete_vex_array_graph( AG G, vertex_type v );
int delete_arc_array_graph( AG G, vertex_type v, vertex_type w );

int traverse_array_graph( AG G, int tag );

#endif /* __ARRAY_GRAPH_H__ */