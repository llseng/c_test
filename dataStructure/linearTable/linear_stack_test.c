#include <stdio.h>
#include "linear_stack.c"

int main(int argc, char const *argv[])
{
    
    printf("help\n");
    printf("CMD\n");
    printf("a add\n");
    printf("g get\n");
    printf("p push\n");
    printf("q quit\n\n");
    
    LinearStack stack;
    int cmd, input, i = 100;
    
    stack = init_linear_stack();
    
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
            if( pop_linear_stack( stack, input ) )
            {
                printf("success\n");
            }else{
                printf("fail\n");
            }
            break;
        
        case 'g':
            if( top_linear_stack( stack, &input ) )
            {
                printf("success\n");
                printf("number %d\n", input);
            }else{
                printf("fail\n");
            }
            break;
            
        case 'p':
            if( push_linear_stack( stack ) )
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
}
