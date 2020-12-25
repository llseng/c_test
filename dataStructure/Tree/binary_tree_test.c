#include <stdio.h>
#include "binary_tree.h"
#include "binary_tree.c"

BinaryTreeNode *binary_tree_create( binary_tree_data_type *,  binary_tree_data_type *, int, int , int, int ); 

int main(int argc, char const *argv[])
{
    
    BinaryTree binary_tree, *bt;
    BinaryTreeNode *t1, *t2, *t3;
    int i, count = 7, list[10][3] = {
        {'A', 'B', 'C'},
        {'B', 'D', 'E'},
        {'D', 'G', 0},
        {'G', 0, 'J'},
        {'E', 'H', 0},
        {'C', 0, 'F'},
        {'F', 'I', 0},
    };
    int pre[10] = {'A', 'B', 'D', 'G', 'J', 'E', 'H', 'C', 'F', 'I'};
    int in[10] = {'G', 'J', 'D', 'B', 'H', 'E', 'A', 'C', 'I', 'F'};
    bt = &binary_tree;
    init_binary_tree( bt );
    create_binary_tree( bt, 'A' );

    for ( i = 0; i < count; i++)
    {
        t1 = locate_binary_tree( bt, list[i][0] );
        if( t1 == NULL ) continue;
        if( list[i][1] ) {
            t2 = malloc_binary_tree_node( list[i][1] );
            if( t2 ) 
            {
                t1->lchild = t2;
            }
        }

        if( list[i][2] ) {
            t3 = malloc_binary_tree_node( list[i][2] );
            if( t3 ) 
            {
                t1->rchild = t3;
            }
        }
    }

    t1 = parent_binary_tree( bt, 'B' );
    if( t1 )
    {
        printf( "'B' parent: '%c'\n", t1->data );
    }else{
        printf( "'B' parent miss\n" );
    }

    t1 = parent_binary_tree( bt, 'A' );
    if( t1 )
    {
        printf( "'A' parent: '%c'\n", t1->data );
    }else{
        printf( "'A' parent miss\n" );
    }

    t2 = lchild_binary_tree( bt, 'E' );
    if( t2 )
    {
        printf( "'E' lchild: '%c'\n", t2->data );
    }else{
        printf( "'E' lchild miss\n" );
    }

    t2 = lchild_binary_tree( bt, 'G' );
    if( t2 )
    {
        printf( "'G' lchild: '%c'\n", t2->data );
    }else{
        printf( "'G' lchild miss\n" );
    }

    t3 = rchild_binary_tree( bt, 'G' );
    if( t3 )
    {
        printf( "'G' rchild: '%c'\n", t3->data );
    }else{
        printf( "'G' rchild miss\n" );
    }

    t3 = rchild_binary_tree( bt, 'E' );
    if( t3 )
    {
        printf( "'E' rchild: '%c'\n", t3->data );
    }else{
        printf( "'E' rchild miss\n" );
    }
    
    printf("recursion\n");
    printf("pre_order\n");
    pre_order_binary_tree( bt, bt_pre_order_recursion );
    printf("in_order\n");
    in_order_binary_tree( bt, bt_in_order_recursion );
    printf("post_order\n");
    post_order_binary_tree( bt, bt_post_order_recursion );

    printf("nrecursion\n");
    printf("pre_order\n");
    pre_order_binary_tree( bt, bt_pre_order_nrecursion );
    printf("in_order\n");
    in_order_binary_tree( bt, bt_in_order_nrecursion );
    printf("post_order\n");
    post_order_binary_tree( bt, bt_post_order_nrecursion );

    printf( "level_order\n" );
    level_order_binary_tree( bt );

    printf( "depth\n" );
    count = depth_binary_tree( bt, bt_depth_recursion );
    printf( "recursion: %d\n", count );
    count = depth_binary_tree( bt, bt_depth_nrecursion );
    printf( "nrecursion: %d\n", count );

    t1 = binary_tree_create( pre, in, 0, 9, 0, 9 );
    printf( "bt_pre_order_nrecursion\n" );
    bt_pre_order_nrecursion( t1 );
    printf( "\n" );

    printf( "bt_in_order_nrecursion\n" );
    bt_in_order_nrecursion( t1 );
    printf( "\n" );
    return 0;
}

BinaryTreeNode *binary_tree_create( binary_tree_data_type *a,  binary_tree_data_type *b, int i, int j, int m, int n )
{
    int k;
    for ( k = m; k <= n; k++)
    {
        if( a[i] == b[k] ) break;
    }
    if( k > n ) return NULL;

    BinaryTreeNode *node = malloc_binary_tree_node( a[i] );

    node->lchild = binary_tree_create( a, b, i+1, i+k-m, m, k-1);
    node->rchild = binary_tree_create( a, b, i+k-m+1, j, k+1, n);

    return node;
} 