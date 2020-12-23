#include <stdio.h>
#include "linear_queue.c"

int main(int argc, char const *argv[])
{
    printf("help\n");
    printf("CMD\n");
    printf("a add\n");
    printf("g get\n");
    printf("p push\n");
    printf("q quit\n\n");
    
    LinearQueue queue;
    int cmd, input, i = 100;
    
    init_linear_queue( &queue );
    
    while ( i-- )
    {
        printf("CMD\n");
        scanf( "%c", &cmd, &input );
        fflush( stdin );
        printf("RET\n");

        switch ( cmd )
        {
        case 'a':
            printf("input number\n");
            scanf( "%d", &input );
            fflush( stdin );
            if( en_linear_queue( &queue, input ) )
            {
                printf("success\n");
            }else{
                printf("fail\n");
            }
            break;
        
        case 'g':
            if( re_linear_queue( &queue, &input ) )
            {
                printf("success\n");
                printf("number %d\n", input);
            }else{
                printf("fail\n");
            }
            break;
            
        case 'p':
            if( de_linear_queue( &queue ) )
            {
                printf("success\n");
            }else{
                printf("fail\n");
            }
            break;
            
        case 'q':
            goto END;
            break;

        default:
            printf("CMD ERROR\n");
            break;
        }

    }
    
    END:{
        printf("END\n");
    }

    return 0;
    return 0;
}
