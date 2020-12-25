#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

BinaryTreeNode *malloc_binary_tree_node( binary_tree_data_type value );
void free_binary_tree_node( BinaryTreeNode *node );

int init_binary_tree( BT bt )
{
    // if( empty_binary_tree( bt ) )
    // {
        bt->root = NULL;
    // }else{
    //     free_binary_tree_node( bt->root );
    // }

    return 1;
}

int empty_binary_tree( BT bt )
{
    if( bt->root == NULL ) return 1;
    return 0;
}

int create_binary_tree( BT bt, binary_tree_data_type value )
{
    BinaryTreeNode *root_node = malloc_binary_tree_node( value );
    if( root_node == NULL ) return 0;
    bt->root = root_node;
    return 1;
}

BinaryTreeNode *locate_binary_tree( BT bt, binary_tree_data_type x )
{
    if( empty_binary_tree( bt ) ) return NULL;
    
    int sign;
    BinaryTreeNode *p = bt->root;
    BinaryTreeLinearTable lt;
    init_btlt( &lt );

    while (p != NULL)
    {
        if( p->data == x ) break;

        if( p->lchild != NULL )
        {
            rpush_btlt( &lt, p->lchild, 0 );
        }

        if( p->rchild != NULL )
        {
            rpush_btlt( &lt, p->rchild, 0 );
        }

        lget_btlt( &lt, &p, &sign );
        lpop_btlt( &lt );
    }
    
    return p;
}

BinaryTreeNode *parent_binary_tree( BT bt, binary_tree_data_type x )
{
    if( empty_binary_tree( bt ) ) return NULL;
    
    int sign;
    BinaryTreeNode *p = bt->root;
    BinaryTreeLinearTable lt;
    init_btlt( &lt );

    while (p != NULL)
    {
        if( p->lchild != NULL )
        {
            if( p->lchild->data == x ) break;
            rpush_btlt( &lt, p->lchild, 0 );
        }

        if( p->rchild != NULL )
        {
            if( p->rchild->data == x ) break;
            rpush_btlt( &lt, p->rchild, 0 );
        }

        lget_btlt( &lt, &p, &sign );
        lpop_btlt( &lt );
    }
    
    return p;
}

BinaryTreeNode *lchild_binary_tree( BT bt, binary_tree_data_type x )
{
    if( empty_binary_tree( bt ) ) return NULL;
    
    int sign;
    BinaryTreeNode *p = bt->root;
    BinaryTreeLinearTable lt;
    init_btlt( &lt );

    while (p != NULL)
    {
        if( p->data == x )
        {
            p = p->lchild;
            break;
        }

        if( p->lchild != NULL )
        {
            rpush_btlt( &lt, p->lchild, 0 );
        }

        if( p->rchild != NULL )
        {
            rpush_btlt( &lt, p->rchild, 0 );
        }

        lget_btlt( &lt, &p, &sign );
        lpop_btlt( &lt );
    }
    
    return p;
}

BinaryTreeNode *rchild_binary_tree( BT bt, binary_tree_data_type x )
{
    if( empty_binary_tree( bt ) ) return NULL;
    
    int sign;
    BinaryTreeNode *p = bt->root;
    BinaryTreeLinearTable lt;
    init_btlt( &lt );

    while (p != NULL)
    {
        if( p->data == x )
        {
            p = p->rchild;
            break;
        }

        if( p->lchild != NULL )
        {
            rpush_btlt( &lt, p->lchild, 0 );
        }

        if( p->rchild != NULL )
        {
            rpush_btlt( &lt, p->rchild, 0 );
        }

        lget_btlt( &lt, &p, &sign );
        lpop_btlt( &lt );
    }
    
    return p;
}

void pre_order_binary_tree( BT bt, void(*f)( BinaryTreeNode * ) )
{
    if( empty_binary_tree( bt ) ) return;
    f( bt->root );
    
    printf( "\n" );
    return ;
}

void in_order_binary_tree( BT bt, void(*f)( BinaryTreeNode * ) )
{
    if( empty_binary_tree( bt ) ) return;
    f( bt->root );
    
    printf( "\n" );
    return ;
}

void post_order_binary_tree( BT bt, void(*f)( BinaryTreeNode * ) )
{
    if( empty_binary_tree( bt ) ) return;
    f( bt->root );
    
    printf( "\n" );
    return ;
}

void level_order_binary_tree( BT bt )
{
    if( empty_binary_tree( bt ) ) return ;
    
    int sign;
    BinaryTreeNode *p = bt->root;
    BinaryTreeLinearTable lt;
    init_btlt( &lt );

    while (p != NULL)
    {
        printf( "%c ", p->data );

        if( p->lchild != NULL )
        {
            rpush_btlt( &lt, p->lchild, 0 );
        }

        if( p->rchild != NULL )
        {
            rpush_btlt( &lt, p->rchild, 0 );
        }

        lget_btlt( &lt, &p, &sign );
        lpop_btlt( &lt );
    }
    
    printf( "\n" );
    return ;
}

// 遍历递归实现
void bt_pre_order_recursion( BinaryTreeNode *n )
{
    if( n == NULL ) return ;
    printf( "%c ", n->data );
    bt_pre_order_recursion( n->lchild );
    bt_pre_order_recursion( n->rchild );

    return ;
}

void bt_in_order_recursion( BinaryTreeNode *n )
{
    if( n == NULL ) return ;
    bt_in_order_recursion( n->lchild );
    printf( "%c ", n->data );
    bt_in_order_recursion( n->rchild );

    return ;
}

void bt_post_order_recursion( BinaryTreeNode *n )
{
    if( n == NULL ) return ;
    bt_post_order_recursion( n->lchild );
    bt_post_order_recursion( n->rchild );
    printf( "%c ", n->data );

    return ;
}

// 遍历非递归实现
void bt_pre_order_nrecursion( BinaryTreeNode *n )
{
    if( n == NULL ) return ;

    int sign;
    BinaryTreeNode *p = n;
    BinaryTreeLinearTable lt;
    init_btlt( &lt );
    
    while( p != NULL || !empty_btlt( &lt ) ) 
    {
        if( p )
        {
            printf( "%c ", p->data );
            lpush_btlt( &lt, p, 0);
            p = p->lchild;
        }else{
            lget_btlt( &lt, &p, &sign );
            lpop_btlt( &lt );
            p = p->rchild;
        }
        
    }

    return ;
}

void bt_in_order_nrecursion( BinaryTreeNode *n )
{
    if( n == NULL ) return ;

    int sign;
    BinaryTreeNode *p = n;
    BinaryTreeLinearTable lt;
    init_btlt( &lt );
    
    while( p != NULL || !empty_btlt( &lt ) ) 
    {
        if( p )
        {
            lpush_btlt( &lt, p, 0);
            p = p->lchild;
        }else{
            lget_btlt( &lt, &p, &sign );
            lpop_btlt( &lt );
            printf( "%c ", p->data );
            p = p->rchild;
        }
    }

    return ;
}

void bt_post_order_nrecursion( BinaryTreeNode *n )
{
    if( n == NULL ) return ;

    int sign = 1;
    BinaryTreeNode *p = n;
    BinaryTreeLinearTable lt;
    init_btlt( &lt );
    
    while( p != NULL || !empty_btlt( &lt ) ) 
    {
        if( p )
        {
            lpush_btlt( &lt, p, 1);
            p = p->lchild;
        }else{
            lget_btlt( &lt, &p, &sign );
            lpop_btlt( &lt );
            if( sign )
            {
                lpush_btlt( &lt, p, 0 );
                p = p->rchild;
            }else{
                printf( "%c ", p->data );
                p = NULL;
            }
        }
    }

    return ;
}

// 树的深度
int depth_binary_tree( BT bt, int (*f)(BinaryTreeNode *n) )
{
    if( empty_binary_tree( bt ) ) return 0;
    return f( bt->root );
}

int bt_depth_recursion( BinaryTreeNode *n )
{
    if( n == NULL ) return 0;
    int ldepth = bt_depth_recursion( n->lchild ) + 1;
    int rdepth = bt_depth_recursion( n->rchild ) + 1;
    if( ldepth >= rdepth )
    {
        return ldepth;
    }else{
        return rdepth;
    }
}

int bt_depth_nrecursion( BinaryTreeNode *n )
{
    if( n == NULL ) return 0;
    int sign = 0;
    BinaryTreeNode *p = n;
    BinaryTreeLinearTable lt;

    init_btlt( &lt );

    rpush_btlt( &lt, p, 1 );

    while ( !empty_btlt( &lt ) )
    {
        lget_btlt( &lt, &p, &sign );
        lpop_btlt( &lt );

        if( p->lchild != NULL )
        {
            rpush_btlt( &lt, p->lchild, sign + 1 );
        }

        if( p->rchild != NULL )
        {
            rpush_btlt( &lt, p->rchild, sign + 1 );
        }
    }
    
    return sign;
}

static BTLTN malloc_btltn( BinaryTreeNode *n, int s );

void init_btlt( BTLT lt )
{
    lt->head = lt->tail = malloc_btltn( NULL, 0 );
    return ;
}

int empty_btlt( BTLT lt )
{
    if( lt->head == lt->tail ) return 1;
    return 0;
}

int full_btlt( BTLT lt )
{
    return 0;
}

int lpush_btlt( BTLT lt, BinaryTreeNode *n, int s )
{
    if( empty_btlt( lt ) ) return rpush_btlt( lt, n, s );
    
    BTLTN node = malloc_btltn( n, s );
    node->next = lt->head->next;
    node->next->previous = node;
    lt->head->next = node;

    return ;
}

int rpush_btlt( BTLT lt, BinaryTreeNode *n, int s )
{
    BTLTN node = malloc_btltn( n, s );
    node->previous = lt->tail;
    lt->tail->next = node;
    lt->tail = node;

    return 1;
}

int lget_btlt( BTLT lt, BinaryTreeNode **n, int *s )
{
    if( empty_btlt( lt ) )
    {
        *n = NULL;
        *s = 0;
        return 0;
    }

    *n = lt->head->next->data;
    *s = lt->head->next->sign;

    return 1;
}

int rget_btlt( BTLT lt, BinaryTreeNode **n, int *s )
{
    if( empty_btlt( lt ) )
    {
        *n = NULL;
        *s = 0;
        return 0;
    }
    
    *n = lt->tail->data;
    *s = lt->tail->sign;

    return 1;
}

int lpop_btlt( BTLT lt )
{
    if( empty_btlt( lt ) ) return 0;
    BTLTN node = lt->head->next;
    lt->head->next = node->next;
    if( lt->tail == node ) 
    {
        lt->tail = lt->head;
    }else{
        lt->head->next->previous = lt->head;
    }

    free( node );
    return 1;
}

int rpop_btlt( BTLT lt )
{
    if( empty_btlt( lt ) ) return 0;
    BTLTN node = lt->tail;
    lt->tail = node->previous;
    lt->tail->next = node->next;

    free( node );
    return 1;
}

BinaryTreeNode *malloc_binary_tree_node( binary_tree_data_type value )
{
    BinaryTreeNode *node = (BinaryTreeNode *)malloc( sizeof( BinaryTreeNode ) );
    
    if( node != NULL )
    {
        node->data = value;
        node->lchild = NULL;
        node->rchild = NULL;
    }

    return node;
}

void free_binary_tree_node( BinaryTreeNode *node )
{
    if( node == NULL ) return ;

    free_binary_tree_node( node->lchild );
    free_binary_tree_node( node->rchild );
    free( node );

    return ;
}

static BTLTN malloc_btltn( BinaryTreeNode *n, int s )
{
    BTLTN node = (BTLTN)malloc( sizeof( BinaryTreeLinearTableNode ) );
    if( node != NULL )
    {
        node->data = n;
        node->sign = s;
        node->next = NULL;
        node->previous = NULL;
    }

    return node;
}