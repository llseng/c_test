/*
 * @Author: llseng 
 * @Date: 2020-07-09 16:12:04 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-10 17:46:15
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "logger.h"

int wm_logger_init( wm_logger_t *logger, char *name ) {
    logger->name = (char *)calloc( strlen( name ) + 1, sizeof( char ) );
    if( logger->name == NULL ) return -1;
    if( strcpy( logger->name, name ) == NULL ) return -2;
    
    logger->handler_len = 0;
    logger->handler_arr = ( wm_logger_handler_t ** )calloc( logger->handler_len + 1, sizeof( wm_logger_handler_t * ) );
    if( logger->handler_arr == NULL ) return -3;

    return 0;
}

int wm_logger_destroy( wm_logger_t *logger ) {
    while( logger->handler_len == 0 ) {
        wm_logger_handler_destroy( *( logger->handler_arr + --logger->handler_len ) );
    }

    free( logger->name );
    free( logger->handler_arr );
    logger->handler_len = 0;

    return 0;
}

int wm_logger_set_name( wm_logger_t *logger, char *name ) {
    logger->name = (char *)realloc( logger->name, strlen( name ) * sizeof( char ) + 1 );
    if( logger->name == NULL ) return -1;
    if( strcpy( logger->name, name ) == NULL ) return -2;

    return 0;
}

int wm_logger_add_handler( wm_logger_t *logger, wm_logger_handler_t *handler ) {
    *( logger->handler_arr + logger->handler_len++ ) = handler;
    logger->handler_arr = ( wm_logger_handler_t ** )realloc( logger->handler_arr, logger->handler_len * sizeof( wm_logger_handler_t * ) );
    if( logger->handler_arr == NULL ) return -1;
    
    return 0;
}

int wm_logger_pop_handler( wm_logger_t *logger ) {
    if( logger->handler_len == 0 ) return 1;
    if( wm_logger_handler_destroy( *( logger->handler_arr + --logger->handler_len ) ) != 0 ) return 2;
    
    logger->handler_arr = ( wm_logger_handler_t ** )realloc( logger->handler_arr, logger->handler_len * sizeof( wm_logger_handler_t * ) );
    if( logger->handler_arr == NULL ) return -1;
    
    return 0;
}

int wm_logger_write( wm_logger_t *logger, int level, char *fmt, ... ) {
    if( !logger->handler_len ) return 0;
    int i;
    char logger_str[ strlen( logger->name ) + 80 + 4 + strlen( fmt ) ], time_str[ 80 ], time_format[] = "%Y-%m-%d %H:%M:%S", level_name[40];
    time_t now_time = time( NULL );
    struct tm * time_tm = localtime( &now_time );
    
    wm_get_level_name( level, level_name );
    strftime( time_str, 80, time_format, time_tm );
    sprintf( logger_str, "[%s] %s.%s: %s", time_str, logger->name, level_name, fmt );
    // strcat( logger_str, fmt );

    va_list args;
    va_start( args, fmt );

    for( i = 0; i < logger->handler_len; i++ ) {
        char mag_str[ (*( logger->handler_arr + i ))->max_line_size ];
        vsprintf( mag_str, logger_str, args );
        wm_logger_handler_write( *( logger->handler_arr + i ), level, mag_str );
    }
    
    va_end( args );

    return 0;
}

int wm_get_level_name( unsigned int level, char *str ) {
    switch (level)
    {
    case LOG_DEBUG:
        strcpy( str ,"DEBUG" );
        break;
    case LOG_INFO:
        strcpy( str ,"INFO" );
        break;
    case LOG_NOTICE:
        strcpy( str ,"NOTICE" );
        break;
    case LOG_WARNING:
        strcpy( str ,"WARNING" );
        break;
    case LOG_ERROR:
        strcpy( str ,"ERROR" );
        break;
    case LOG_CRITICAL:
        strcpy( str ,"CRITICAL" );
        break;
    
    default:
        strcpy( str ,"DEBUG" );
        break;
    }

    return 0;
}

int wm_logger_handler_init( wm_logger_handler_t *handler, char *file_addr, unsigned int level ) {
    handler->file_dir = (char *)calloc( 1, sizeof( char ) );
    if( handler->file_dir == NULL ) return -1;
    handler->file_name = (char *)calloc( 1, sizeof( char ) );
    if( handler->file_name == NULL ) return -2;

    if( wm_logger_handler_set_file_addr( handler, file_addr ) != 0 ) return 1;
    if( wm_logger_handler_set_level( handler, level ) != 0 ) return 2;
    if( wm_logger_handler_set_max_line_size( handler, DEFAULT_MAX_LINE_SIZE ) != 0 ) return 3;
    if( wm_logger_handler_set_max_file_size( handler, DEFAULT_MAX_FILE_SIZE ) != 0 ) return 4;

    return 0;
}

int wm_logger_handler_destroy( wm_logger_handler_t *handler ) {
    if( handler->fd != NULL ) fclose( handler->fd );
    if( handler->file_dir != NULL ) free( handler->fd );
    if( handler->file_name != NULL ) free( handler->fd );

    handler->level = LOG_DEBUG;
    handler->max_line_size = DEFAULT_MAX_LINE_SIZE;
    handler->max_file_size = DEFAULT_MAX_FILE_SIZE;

    return 0;
}

int wm_logger_handler_set_file_addr( wm_logger_handler_t *handler, char *file_addr ){
    
    char *pos;
    int dir_len, name_len;
    pos = strrchr( file_addr, '/' );
    pos = pos? pos: file_addr;

    dir_len = pos != file_addr? abs( pos - file_addr ): 0;
    name_len = strlen( pos + 1 );

    handler->file_dir = (char *)realloc( handler->file_dir, (dir_len + 1) * sizeof( char ) );
    if( handler->file_dir == NULL ) return -1;
    handler->file_name = (char *)realloc( handler->file_name, (name_len + 1) * sizeof( char ) );
    if( handler->file_name == NULL ) return -2;

    if( strcpy( handler->file_name, pos + 1 ) == NULL ) return -3;
    if( strncpy( handler->file_dir, file_addr, dir_len ) == NULL ) return -4;

    handler->fd = fopen( file_addr, "ab+" );
    if( handler->fd == NULL ) return -5;

    return 0;
}

int wm_logger_handler_set_level( wm_logger_handler_t *handler, unsigned int level ) {
    handler->level = level? level: LOG_DEBUG;

    return 0;
}

int wm_logger_handler_set_max_line_size( wm_logger_handler_t *handler, unsigned int max_line_size ) {
    handler->max_line_size = max_line_size? max_line_size: DEFAULT_MAX_LINE_SIZE;

    return 0;
}

int wm_logger_handler_set_max_file_size( wm_logger_handler_t *handler, unsigned int max_file_size ) {
    handler->max_file_size = max_file_size? max_file_size: DEFAULT_MAX_FILE_SIZE;

    return 0;
}

int wm_logger_handler_write( wm_logger_handler_t *handler, unsigned int level, char *message ) {

    if( handler->fd == NULL ) return 1;
    if( strlen( message ) == 0 ) return 2;

    int put_len;
    put_len = fputs( message, handler->fd );
    if( put_len < 0 ) return -1; 

    return 0;
}
