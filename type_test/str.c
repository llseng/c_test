/*
* @Author: llseng
* @Date:   2020-06-17 19:15:27
* @Last Modified by:   llseng
* @Last Modified time: 2020-06-24 18:05:55
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

    struct m_t a = { 1, '1', "123456" };

    printf("%d %d\n", sizeof( a ), sizeof( a.c ) );

    
    char *p_str, str[] = "resource: net::ERR_CONNECTION_TIMED_OUT";
    p_str = str;
    int str_len = strlen( str );
    int i = 0;

    printf("str = '%s', str_len = %d\n", str, str_len);
    printf("*p_str = '%c' = %d, p_str = '%s'\n", *p_str, *p_str, p_str);

    printf("*p_str >> 4 = %d\n", *p_str >> 4);

    printf("*(p_str + %d) '%c' is_abc %d\n", i, *(p_str + i), is_abc( *(p_str + i) ) );
    i++;
    printf("*(p_str + %d) '%c' is_labc %d\n", i, *(p_str + i), is_labc( *(p_str + i) ) );
    i++;
    printf("*(p_str + %d) '%c' is_uabc %d\n", i, *(p_str + i), is_uabc( *(p_str + i) ) );
    i++;
    printf("*(p_str + %d) '%c' char_to_lower %c = %c\n", i, *(p_str + i), char_to_lower( *(p_str + i) ), *(p_str + i) );

    i++;
    printf("*(p_str + %d) '%c' char_to_upper %c = %c\n", i, *(p_str + i), char_to_upper( *(p_str + i) ), *(p_str + i) );
    i++;
    printf("p_str[0] '%c' char_to_upper %c = %c\n", p_str[0], p_str[0] = char_to_upper( p_str[0] ), p_str[0] );

    printf("p_str[0] '%c'\n", p_str[0]);
    printf("str = '%s', str_len = %d\n", str, str_len);

    char str1[ str_len + 1 ], str2[ str_len + 1 ];

    strcpy(str1, str);
    strcpy(str2, str);

    printf("str1 = '%s', len = %d\n", str1, strlen( str1 ) );
    printf("str2 = '%s', len = %d\n", str2, strlen( str2 ) );

    str_to_lower( str1 );
    str_to_upper( str2 );

    printf("str1 lower = '%s', len = %d\n", str1, strlen( str1 ) );
    printf("str2 upper = '%s', len = %d\n", str2, strlen( str2 ) );

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