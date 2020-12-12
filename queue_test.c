/*
* @Author: llseng
* @Date:   2020-04-03 11:31:25
* @Last Modified by:   llseng
* @Last Modified time: 2020-04-03 16:47:53
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/**
 * 队列数据
 */
typedef char * CQData;
/**
 * 队列节点
 */
typedef struct cqueue_node {
    CQData data;
    struct cqueue_node * next;
} CQNode;
/**
 * 队列
 */
typedef struct cqueue {
    CQNode *start, *end;
} CQ;
/**
 * 入队
 */
int en_cqueue( CQ *q, CQData data );
/**
 * 出队
 */
int de_cqueue( CQ *q, CQData* value );

int main(int argc, char const *argv[])
{
    CQ q;
    CQNode *s = (CQNode *)malloc( sizeof(CQNode) );
    s->data = 0;
    s->next = NULL;

    q.start = s;
    q.end = s;
    printf("CQData size: %d,char size: %d\n", sizeof( CQData ), sizeof( char ) );
    int en_status;
    en_status = en_cqueue( &q, "123456");
    printf("1 en_status = %d\n", en_status);
    en_status = en_cqueue( &q, "26555565616");
    printf("2 en_status = %d\n", en_status);
    en_status = en_cqueue( &q, "3asdasdasdq");
    printf("3 en_status = %d\n", en_status);
    en_status = en_cqueue( &q, "4awafssaga");
    printf("4 en_status = %d\n", en_status);
    
    int de_status;
    CQData v1;
    CQData v2;
    CQData v3;
    CQData v4;
    CQData v5;

    de_status = de_cqueue( &q, &v1);
    printf("de_status = %d,v1: %s\n", de_status, v1);
    de_status = de_cqueue( &q, &v2);
    printf("de_status = %d,v2: %s\n", de_status, v2);
    de_status = de_cqueue( &q, &v3);
    printf("de_status = %d,v3: %s\n", de_status, v3);
    de_status = de_cqueue( &q, &v4);
    printf("de_status = %d,v4: %s\n", de_status, v4);
    de_status = de_cqueue( &q, &v5);
    printf("de_status = %d,v5: %s\n", de_status, v5);

    /* code */
    return 0;
}

int en_cqueue( CQ *q, CQData data ) {
    
    CQNode *new_node = (CQNode *)malloc( sizeof(CQNode) );//创建新数据节点,分配内存(:

    // printf("data: %s\n", data);
    size_t len = strlen( data ); //数据长度
    // printf("len: %d,data size: %d\n", len, sizeof( data ));
    
    new_node->data = (CQData)malloc( len + 2*sizeof( char ) ); // 为节点数据分配内存

    //节点数据赋值
    int i;
    for (i = 0; i < len; i++)
    {
        new_node->data[i] = data[i]; 
    }
    new_node->data[i] = '\0';

    // printf("%s\n", new_node->data);
    // strcpy( new_node.data, "asda" );
    
    new_node->next = NULL;
    //
    q->end->next = new_node; //队尾下一列连接 新节点
    q->end = new_node; //重置队尾

    return 1;
}

int de_cqueue( CQ *q, CQData* value ) {

    if( q->start == q->end ) { // 队头尾相同 队列无节点
        *value = NULL; // 置空
        return 0;
    }

    CQNode *temp_node = q->start->next; //临时节点 获取对头下一列

    printf("t: %s,p: %s\n", temp_node->data, q->start->next->data);

    *value = temp_node->data; //

    q->start->next = temp_node->next; //重置队头下一列为临时节点下一列

    if( q->end == temp_node ) { //队尾为临时节点 (:队空
        printf("in end\n");
        q->end = q->start; //重置队列
    }

    free( temp_node ); //释放

    return 1;
}