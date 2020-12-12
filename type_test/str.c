/*
* @Author: llseng
* @Date:   2020-06-17 19:15:27
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-10 10:23:47
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct m_t {
    int a;
    char b;
    char c[10];
};

int is_abc( int );
int is_labc( int );
int is_uabc( int );
int char_to_lower( int );
int char_to_upper( int );
char *str_to_lower( char * );
char *str_to_upper( char * );

int main() {

    char str1[10], str2[10] = "123456789", *str3 = (char *)calloc( 10, sizeof(char) );
    
    printf( "str1 '%s' len %d\n", str1, strlen( str1 ) );
    printf( "str2 '%s' len %d\n", str2, strlen( str2 ) );
    printf( "str3 '%s' len %d\n", str3, strlen( str3 ) );

    memset( str1, 0, strlen(str1) );
    memset( str3, 0, strlen(str3) );

    strcpy( str1, str2 );
    strcpy( str3, str2 );
    
    printf( "str1 '%s' len %d\n", str1, strlen( str1 ) );
    printf( "str2 '%s' len %d\n", str2, strlen( str2 ) );
    printf( "str3 '%s' len %d\n", str3, strlen( str3 ) );

    memset( str1, 0, strlen(str1) );
    memset( str3, 0, strlen(str3) );

    strncpy( str1, str2, 5 );
    strncpy( str3, str2, 5 );
    
    printf( "str1 '%s' len %d\n", str1, strlen( str1 ) );
    printf( "str2 '%s' len %d\n", str2, strlen( str2 ) );
    printf( "str3 '%s' len %d\n", str3, strlen( str3 ) );

    memset( str1, 0, strlen(str1) );
    memset( str3, 0, strlen(str3) );

    strncpy( str1, str2, 0 );
    if( str1 == NULL ) printf( "str1 = NULL\n");
    strncpy( str3, str2, 0 );
    if( str3 == NULL ) printf( "str3 = NULL\n");
    
    printf( "str1 '%s' len %d\n", str1, strlen( str1 ) );
    printf( "str2 '%s' len %d\n", str2, strlen( str2 ) );
    printf( "str3 '%s' len %d\n", str3, strlen( str3 ) );

    int i = 10;
    while( i-- ) {
        printf( "%s %s\n", __DATE__, __TIME__ );
        sleep( 1 );
    }

    return 0;
}

int is_abc( int c ) {
    // 字母ASCII码 A 0b010 00001 z 0b011 11010
    int l_lb = 0b010;
    int l_ub = 0b011;
    int r_lb = 0b00001;
    int r_ub = 0b11010;
    int b = 5;

    int l = c >> b, r = c & 0b00011111;

    if( l < l_lb || l > l_ub ) {
        return 0;
    }

    if( r < r_lb || r > r_ub ) {
        return 0;
    }

    return 1;

}

int is_labc( int c ) {

    int l_b = 0b011;
    int r_lb = 0b00001;
    int r_ub = 0b11010;
    int b = 5;

    int l = c >> b, r = c & 0b00011111;

    if( l ^ l_b ) {
        return 0;
    }

    if( r < r_lb || r > r_ub ) {
        return 0;
    }

    return 1;
}

int is_uabc( int c ) {

    int l_b = 0b010;
    int r_lb = 0b00001;
    int r_ub = 0b11010;
    int b = 5;

    int l = c >> b, r = c & 0b00011111;

    if( l ^ l_b ) {
        return 0;
    }

    if( r < r_lb || r > r_ub ) {
        return 0;
    }

    return 1;
}

int char_to_lower( int c ) {
    if( is_abc( c ) && is_uabc( c ) ) {
        int b = 0b00100000;
        c = c | b;
    }

    return c;
}

int char_to_upper( int c ) {
    if( is_abc( c ) && is_labc( c ) ) {
        int b = 0b11011111;
        c = c & b;
    }

    return c;
}

char *str_to_lower( char *str ) {
    int i, str_len = strlen( str );
    for (i = 0; i < str_len; ++i)
    {
        str[i] = char_to_lower( str[i] );
    }

    return str;
}

char *str_to_upper( char *str ) {
    int i, str_len = strlen( str );
    for (i = 0; i < str_len; ++i)
    {
        str[i] = char_to_upper( str[i] );
    }

    return str;
}