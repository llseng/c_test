/*
* @Author: llseng
* @Date:   2020-06-18 11:21:20
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-18 16:56:11
*/

#include <stdio.h>
#include "queue.c"

void tt( void ) {
    printf("tt func\n");
}

int main(int argc, char const *argv[])
{
    MQ_link mql, *mq;
    mq = &mql;
    MQ_init( mq );

    printf("mq->size = %d\n", mq->size);

    int a = 1;

    MQ_en( mq, (MQ_data)&a );

    printf("mq->size = %d\n", mq->size);

    int b = 2;
    MQ_en( mq, (MQ_data)&tt );
    printf("mq->size = %d\n", mq->size);
    
    char *c = "asdasiasda";
    MQ_en( mq, (MQ_data)&c );
    printf("mq->size = %d\n", mq->size);

    MQ_data v1;
    unsigned int status;
    status = MQ_de( mq, &v1 );
    printf("mq->size = %d\n", mq->size);
    // status = MQ_de( mq, &v );
    // printf("status = %d ,v = %d\n", status, v);
    printf("status = %d, v1 = %d\n", status, *(int *)v1);
    
    // MQ_data v2;
    void (* v2)(void);
    status = MQ_de( mq, (MQ_data)&v2 );
    printf("mq->size = %d\n", mq->size);
    // status = MQ_de( mq, &v );
    // printf("status = %d ,v = %d\n", status, v);
    v2();
    printf("status = %d, v2 = %d\n", status, v2);

    MQ_data v3;
    status = MQ_de( mq, &v3 );
    printf("mq->size = %d\n", mq->size);
    // status = MQ_de( mq, &v );
    // printf("status = %d ,v = %d\n", status, v);
    printf("status = %d, v3 = %s\n", status, *(char **)v3);

    MQ_data v4;
    status = MQ_de( mq, &v4 );
    printf("mq->size = %d\n", mq->size);
    // status = MQ_de( mq, &v );
    // printf("status = %d ,v = %d\n", status, v);
    printf("status = %d, v4 = %d\n", status, v4);

    return 0;
}