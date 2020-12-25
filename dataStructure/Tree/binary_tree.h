#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef int binary_tree_data_type;

typedef struct binary_tree_node
{
    binary_tree_data_type data;
    struct binary_tree_node *lchild, *rchild;
} BinaryTreeNode;

typedef struct binary_tree
{
    struct binary_tree_node *root;
} BinaryTree, *BT;

int init_binary_tree( BT bt );
int empty_binary_tree( BT bt );
int create_binary_tree( BT bt, binary_tree_data_type value );
BinaryTreeNode *locate_binary_tree( BT bt, binary_tree_data_type x );
BinaryTreeNode *parent_binary_tree( BT bt, binary_tree_data_type x );
BinaryTreeNode *lchild_binary_tree( BT bt, binary_tree_data_type x );
BinaryTreeNode *rchild_binary_tree( BT bt, binary_tree_data_type x );
void pre_order_binary_tree( BT bt, void(*f)( BinaryTreeNode * ) );
void in_order_binary_tree( BT bt, void(*f)( BinaryTreeNode * ) );
void post_order_binary_tree( BT bt, void(*f)( BinaryTreeNode * ) );
void level_order_binary_tree( BT bt );
// 遍历递归实现
void bt_pre_order_recursion( BinaryTreeNode *n );
void bt_in_order_recursion( BinaryTreeNode *n );
void bt_post_order_recursion( BinaryTreeNode *n );
// 遍历非递归实现
void bt_pre_order_nrecursion( BinaryTreeNode *n );
void bt_in_order_nrecursion( BinaryTreeNode *n );
void bt_post_order_nrecursion( BinaryTreeNode *n );
// 树的深度
int depth_binary_tree( BT bt, int (*f)(BinaryTreeNode *n) );
int bt_depth_recursion( BinaryTreeNode *n );
int bt_depth_nrecursion( BinaryTreeNode *n );

typedef struct binary_tree_linear_table_node
{
    BinaryTreeNode *data;
    int sign;
    struct binary_tree_linear_table_node *previous, *next;
} BinaryTreeLinearTableNode, *BTLTN;

typedef struct binary_tree_linear_table
{
    BinaryTreeLinearTableNode *head, *tail;
} BinaryTreeLinearTable, *BTLT;

void init_btlt( BTLT lt );
int empty_btlt( BTLT lt );
int full_btlt( BTLT lt );
int lpush_btlt( BTLT lt, BinaryTreeNode *n, int s );
int rpush_btlt( BTLT lt, BinaryTreeNode *n, int s );
int lget_btlt( BTLT lt, BinaryTreeNode **n, int *s );
int rget_btlt( BTLT lt, BinaryTreeNode **n, int *s );
int lpop_btlt( BTLT lt );
int rpop_btlt( BTLT lt );

#endif /* __BINARY_TREE_H__ */