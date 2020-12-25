#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree.c"

int main(int argc, char const *argv[])
{
    int new_htlen, htlen = 6;
    HuffmanTree new_ht, ht = (HuffmanTree)malloc( sizeof( HuffmanTreeNode ) * htlen );
    
    init_huffman_tree( ht, htlen );

    (ht + 0)->data = 'A';
    (ht + 0)->power = 3.6;
    (ht + 1)->data = 'B';
    (ht + 1)->power = 1.2;
    (ht + 2)->data = 'C';
    (ht + 2)->power = 6.6;
    (ht + 3)->data = 'D';
    (ht + 3)->power = 5.1;
    (ht + 4)->data = 'E';
    (ht + 4)->power = 4.0;
    (ht + 5)->data = 'F';
    (ht + 5)->power = 0.2;

    print_huffman_tree( ht, htlen );

    create_huffman_tree( ht, htlen, &new_ht, &new_htlen );
    
    print_huffman_tree( new_ht, new_htlen );

    return 0;
}