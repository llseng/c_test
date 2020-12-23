#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__

typedef struct linear_data
{
    int id;
    char name[20];
    int sex;
    int age;
    int score;
} LinearData;

typedef struct linear_node
{
    LinearData data;
    struct linear_node * next;
} LinearNode, *LinearList;

LinearList init_linear_list( void );
int insert_linear_list( LinearList list, LinearData data, int i );
int length_linear_list( LinearList list );
int delete_linear_list( LinearList list, int i );
LinearNode *get_linear_list( LinearList list, int i );
LinearNode *locate_linear_list( LinearList list, LinearData data );

#endif /** __LINEAR_TABLE_H__ */