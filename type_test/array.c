#include <stdio.h>
#include <stdlib.h>
#define MATRIX_MAX 10
#define MATRIX_DEF_VALUE 0

int init_matrix( int M[][MATRIX_MAX], int );
int del_matrix_vex( int M[][MATRIX_MAX], int, int );
int show_matrix( int M[][MATRIX_MAX], int );

int main(int argc, char const *argv[])
{
    int mm[ MATRIX_MAX ][ MATRIX_MAX ], dvex, i, j;
    dvex = 4;

    init_matrix( mm, MATRIX_MAX );

    for ( i = 0; i < MATRIX_MAX; i++)
    {
        if( i == dvex ) continue;
        for ( j = 0; j < MATRIX_MAX; j++)
        {
            if( j == dvex ) continue;
            mm[ i ][ j ] = 1;
        }
    }
    show_matrix( mm, MATRIX_MAX );
    del_matrix_vex( mm, 4, MATRIX_MAX );

    return 0;
}

int init_matrix( int M[][MATRIX_MAX], int len )
{
    int i, j;
    i = j = len;
    for (i = 0; i < len; i++)
    {
        for ( j = 0; j < len; j++)
        {
            M[ i ][ j ] = MATRIX_DEF_VALUE;
        }
        
    }
    
    return 0;
}

int del_matrix_vex( int M[][MATRIX_MAX], int vex, int len )
{
    int i, j;
    len--;

    for ( i = vex; i < len; i++)
    {
        for ( j = 0; j < len; j++)
        {
            if( j < vex )
            {
                M[ i ][ j ] = M[ i + 1 ][ j ];
                M[ j ][ i ] = M[ j ][ i + 1 ];
                M[ i + 1 ][ j ] = MATRIX_DEF_VALUE;
                M[ j ][ i + 1 ] = MATRIX_DEF_VALUE;
            }else{
                if( j < i ) continue;
                M[ i ][ j ] = M[ i + 1 ][ j + 1 ];
                M[ j ][ i ] = M[ j + 1 ][ i + 1 ];
                M[ i + 1 ][ j + 1 ] = MATRIX_DEF_VALUE;
                M[ j + 1 ][ i + 1 ] = MATRIX_DEF_VALUE;
            }

            show_matrix( M, len + 1 );
        }
        
    }

    return 0;
}

int show_matrix( int M[][MATRIX_MAX], int len )
{
    int i, j;

    printf("----------\n");

    for ( i = 0; i < len; i++)
    {
        for ( j = 0; j < len; j++)
        {
            printf("%d  ", M[ i ][ j ]);
        }
        printf("\n");
    }
    
    printf("\n");
    usleep(100000);
#ifdef __WIN32__
    system("cls");
#endif

#ifdef linux
    system("clear");
#endif

    return 0;
}