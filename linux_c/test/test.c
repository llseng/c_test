/*
* @Author: llseng
* @Date:   2020-06-28 11:27:04
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-30 14:52:33
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <mqueue.h>

int main(int argc, char const *argv[])
{
    printf("WNOHANG : %d\n", WNOHANG);

    mqd_t mq;
    struct mq_attr mqAttr;
    mq = mq_open( "mq_test", O_CREAT|O_EXCL );

    mq_getattr( mq, &mqAttr );

    printf("mq_flags %ld\n", mqAttr.mq_flags); /* Message queue flags. 0 or O_NONBLOCK */

    printf("mq_maxmsg %ld\n", mqAttr.mq_maxmsg); /* Maximum number of messages.  */

    printf("mq_msgsize %ld\n", mqAttr.mq_msgsize); /* Maximum message size.  */

    printf("mq_curmsgs %ld\n", mqAttr.mq_curmsgs); /* Number of messages currently queued.  */

    return 0;
}