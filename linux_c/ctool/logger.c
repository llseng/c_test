/*
 * @Author: llseng 
 * @Date: 2020-07-09 16:12:04 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-13 17:38:41
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "logger.h"

static int wm_logger_handler_fopen( wm_logger_handler_t *handler );

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
    char logger_str[ strlen( logger->name ) + 80 + 44 + strlen( fmt ) ], time_str[ 80 ], time_format[] = "%Y-%m-%d %H:%M:%S", level_name[40];
    time_t now_time = time( NULL );
    struct tm * time_tm = localtime( &now_time );
    
    wm_logger_get_level_name( level, level_name );
    strftime( time_str, 80, time_format, time_tm );
    sprintf( logger_str, "[%s] %s.%s: %s;\n", time_str, logger->name, level_name, fmt );
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

int wm_logger_get_level_name( unsigned int level, char *str ) {
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
    handler->file_suffix = (char *)calloc( 1, sizeof( char ) );
    if( handler->file_name == NULL ) return -3;
    
    handler->fd = NULL;

    if( wm_logger_handler_set_file_addr( handler, file_addr ) != 0 ) return 1;
    if( wm_logger_handler_set_level( handler, level ) != 0 ) return 2;
    if( wm_logger_handler_set_max_line_size( handler, DEFAULT_MAX_LINE_SIZE ) != 0 ) return 3;
    if( wm_logger_handler_set_max_file_size( handler, DEFAULT_MAX_FILE_SIZE ) != 0 ) return 4;

    handler->write_count = 0;

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
    if( handler->fd != NULL ) fclose( handler->fd );

    char *pos;
    int dir_len, name_len;
    pos = strrchr( file_addr, '/' );
    pos = pos? pos + 1: file_addr;

    dir_len = pos != file_addr? abs( pos - file_addr ) - 1: 0;
    name_len = strlen( pos );

    handler->file_dir = (char *)realloc( handler->file_dir, (dir_len + 1) * sizeof( char ) );
    if( handler->file_dir == NULL ) return -1;
    handler->file_name = (char *)realloc( handler->file_name, (name_len + 1) * sizeof( char ) );
    if( handler->file_name == NULL ) return -2;

    if( strcpy( handler->file_name, pos ) == NULL ) return -3;
    if( strncpy( handler->file_dir, file_addr, dir_len ) == NULL ) return -4;

    if( wm_logger_handler_fopen( handler ) != 0 ) return -5;

    return 0;
}

int wm_logger_handler_set_file_suffix( wm_logger_handler_t *handler, char *file_suffix ) {
    int suffix_len;
    suffix_len = strlen( file_suffix );

    handler->file_suffix = (char *)realloc( handler->file_suffix, (suffix_len + 1) * sizeof( char ) );
    if( handler->file_suffix == NULL ) return -1;

    if( strcpy( handler->file_suffix, file_suffix ) == NULL ) return -2;

    if( wm_logger_handler_fopen( handler ) != 0 ) return -3;

    return 0;
}

static int wm_logger_handler_fopen( wm_logger_handler_t *handler ) {
    int dir_len, name_len, suffix_len, addr_len;
    dir_len = strlen( handler->file_dir );
    name_len = strlen( handler->file_name );
    suffix_len = strlen( handler->file_suffix );
    addr_len += dir_len + name_len + suffix_len;

    if( !addr_len ) return -1;
    addr_len += 4;

    char addr[ addr_len ];
    *addr = '\0';

    if( strcat( addr, handler->file_dir ) == NULL ) return -2;
    if( strcat( addr, handler->file_name ) == NULL ) return -3;
    if( suffix_len ) {
        if( strcat( addr, handler->file_suffix ) == NULL ) return -4;
    }

    if( handler->fd != NULL ) fclose( handler->fd );
    handler->fd = fopen( addr, "ab+" );
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
    if( wm_logger_in_level( handler->level ) ) {
        if( level < handler->level ) return 1;
    }else{
        if( (level & handler->level) == 0 ) return 1;
    }

    if( handler->fd == NULL ) return 2;
    if( strlen( message ) == 0 ) return 3;
    
    if( fputs( message, handler->fd ) < 0 ) return -1; 
    fflush( handler->fd ); //将文件缓冲写入到文件
    handler->write_count++;

    if( (handler->write_count % WRITE_COUNT_MOD) == 1 ) {
        long fd_pos = ftell( handler->fd );

        if( fd_pos < 0 ) return -2;
        if( fd_pos > handler->max_file_size ) {
            time_t now_time = time( NULL );
            char suffix[ 20 ];
            srand( now_time );
            printf( "max_file_size %d\n", handler->max_file_size );
            if( sprintf( suffix, ".%d-%04d", now_time, rand() % 10000 ) < 0 ) return -3;
            
            if( wm_logger_handler_set_file_suffix( handler, suffix ) != 0 ) return 5;

        }
    }

    return 0;
}

int wm_logger_get_name( wm_logger_t *logger, char *str) {
    if( strcpy( str, logger->name ) == NULL ) return -1;

    return 0;
}

int wm_logger_handler_get_file_addr( wm_logger_handler_t *handler, char *str ) {
    if( strcpy( str, "" ) == NULL ) return -1;
    if( strlen( handler->file_dir ) ) {
        if( strcat( str, handler->file_dir ) == NULL ) return -2;
        if( strcat( str, "/" ) == NULL ) return -3;
    }

    if( strcat( str, handler->file_name ) == NULL ) return -4;
    
    return 0;
}

int wm_logger_in_level( unsigned int level ) {
    int s = 0;
    switch (level)
    {
    case LOG_DEBUG:
    case LOG_INFO:
    case LOG_NOTICE:
    case LOG_WARNING:
    case LOG_ERROR:
    case LOG_CRITICAL:
        s = 1;
        break;
    }

    return s;
}