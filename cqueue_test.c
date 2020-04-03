/*
* @Author: llseng
* @Date:   2020-04-03 11:31:25
* @Last Modified by:   llseng
* @Last Modified time: 2020-04-03 17:26:29
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "cqueue.h"

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
    // sleep( 1 );
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