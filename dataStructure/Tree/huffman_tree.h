#ifndef __HUFFMAN_TREE_H__
#define __HUFFMAN_TREE_H__

typedef int huffman_tree_node_data;

typedef struct huffman_tree_node
{
    huffman_tree_node_data data;
    float power;
    int parent, lchild, rchild;
} HuffmanTreeNode, *HuffmanTree;

void init_huffman_tree( HuffmanTree ht, int htlen );
HuffmanTree create_huffman_tree( HuffmanTreeNode *nodes, int nodelen, HuffmanTree *ht, int *htlen );
void print_huffman_tree( HuffmanTree ht, int htlen );

#endif /* __HUFFMAN_TREE_H__ */