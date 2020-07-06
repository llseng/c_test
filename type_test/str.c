/*
* @Author: llseng
* @Date:   2020-06-17 19:15:27
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-06 10:45:06
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

    char str1, str2[10] = "123", str3[3][10] = {"123","456","789"}, *strp1[3], **strp2;
    strp1[0] = str3[0];
    strp1[1] = str3[1];
    strp1[2] = str3[2];
    strp2 = strp1;

    printf( "strp1[0][0] = %c\n", strp1[0][0] );
    printf( "*strp1[0] = %c\n", *strp1[0] );
    printf( "**strp1 = %c\n", **strp1 );

    printf( "strp1 = %p\n", strp1 );
    printf( "str3 = %p\n", str3 );
    printf( "str3[0] = %p\n", str3[0] );
    printf( "str3[0][0] = %p\n", str3[0][0] );

    printf( "**strp2 = %c\n", **strp2 );

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