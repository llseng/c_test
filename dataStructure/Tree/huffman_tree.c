#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "huffman_tree.h"

void init_huffman_tree( HuffmanTree ht, int htlen )
{
    int i;
    for ( i = 0; i < htlen; i++)
    {
        (ht + i )->data = '.';
        (ht + i )->power = 0.0;
        (ht + i )->parent = -1;
        (ht + i )->lchild =  (ht + i )->rchild = 0;
    }
    
    return ;
}

HuffmanTree create_huffman_tree( HuffmanTreeNode *nodes, int nodelen, HuffmanTree *ht, int *htlen )
{
    if( nodes == NULL || nodelen <= 0 )
    {
        *ht = NULL;
        *htlen = 0;
        return NULL;
    }

    int i, j, l, r;
    float m, n;

    *htlen = nodelen * 2 - 1;
    *ht = (HuffmanTree)malloc( sizeof( HuffmanTreeNode ) * *htlen );

    for ( i = 0; i < nodelen; i++)
    {
        (*ht + i )->data = (nodes + i)->data;
        (*ht + i )->power = (nodes + i)->power;
        (*ht + i )->parent = (nodes + i)->parent;
        (*ht + i )->lchild = (nodes + i)->lchild;
        (*ht + i )->rchild = (nodes + i)->rchild;
    }

    init_huffman_tree( (*ht + nodelen ), *htlen - nodelen );

    for ( i = nodelen; i < *htlen; i++)
    {
        m = FLT_MAX, n = FLT_MAX;
        for ( j = 0; j < i; j++)
        {
            if( (*ht + j)->parent >= 0 ) continue;

            if( (*ht + j)->power < n )
            {
                if( (*ht + j)->power < m )
                {
                    n = m;
                    r = l;
                    m = (*ht + j)->power;
                    l = j;
                }else{
                    n = (*ht + j)->power;
                    r = j;
                }
            }

        }

        (*ht + i)->data = '.';
        (*ht + i)->power = m + n;
        (*ht + i)->lchild = l;
        (*ht + i)->rchild = r;

        (*ht + l)->parent = i;
        (*ht + r)->parent = i;
        
    }

    return *ht;

}

void print_huffman_tree( HuffmanTree ht, int htlen )
{
    printf("key\tpower\tdata\tparent\tlchild\trchild\n");
    int i;
    for (i = 0; i < htlen; i++)
    {
        printf( "%d\t%2.2f\t%c\t%d\t%d\t%d\n", i, (ht + i)->power, (ht + i)->data, (ht + i)->parent, (ht + i)->lchild, (ht + i)->rchild);
    }
    printf("---\n");
    return ;
}