/*
* @Author: llseng
* @Date:   2020-06-28 11:27:04
* @Last Modified by:   llseng
* @Last Modified time: 2020-07-01 14:56:13
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <mqueue.h>
#include <pthread.h>

int main(int argc, char const *argv[])
{
    printf("WNOHANG : %d\n", WNOHANG);

    struct mq_attr mq_Attr;
    memset( &mq_Attr, 0, sizeof( mq_Attr ) ); //数据置零
    mq_Attr.mq_flags = 0;
    mq_Attr.mq_maxmsg = 11;
    mq_Attr.mq_msgsize = 11;
    mqd_t mq;
    struct mq_attr mqAttr;
    mq = mq_open( "/mq_test", O_RDONLY | O_CREAT, 0777, &mq_Attr );
    printf("O_CREAT %d ,O_EXCL %d\n", O_CREAT, O_EXCL);
    if( mq < 0 ) {
        printf("mq = %d\n", mq);
        perror("mq_open");
        return 0;
    }
    mq_getattr( mq, &mqAttr );

    printf("mq_flags %ld\n", mqAttr.mq_flags); /* Message queue flags. 0 or O_NONBLOCK */

    printf("mq_maxmsg %ld\n", mqAttr.mq_maxmsg); /* Maximum number of messages.  */

    printf("mq_msgsize %ld\n", mqAttr.mq_msgsize); /* Maximum message size.  */

    printf("mq_curmsgs %ld\n", mqAttr.mq_curmsgs); /* Number of messages currently queued.  */

    mq_unlink( "/mq_test" );
    mq_close( mq );

    char str_buf[100];
    snprintf(str_buf, sizeof( str_buf ), "%ld", mqAttr.mq_flags);
    printf("str_buf %s.\n", str_buf);

    printf("SCHED_FIFO min %d max %d\n", sched_get_priority_min(SCHED_FIFO), sched_get_priority_max(SCHED_FIFO));
    printf("SCHED_RR min %d max %d\n", sched_get_priority_min(SCHED_RR), sched_get_priority_max(SCHED_RR));
    printf("SCHED_OTHER min %d max %d\n", sched_get_priority_min(SCHED_OTHER), sched_get_priority_max(SCHED_OTHER));

    return 0;
}