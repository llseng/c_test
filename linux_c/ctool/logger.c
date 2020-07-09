/*
 * @Author: llseng 
 * @Date: 2020-07-09 16:12:04 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-09 19:32:04
 */
#include <string.h>
#include <stdlib.h>
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

int wm_logger_write( wm_logger_t *logger, int level, ... );

int wm_logger_handler_init( wm_logger_handler_t *handler, char *file_addr, unsigned int level ) {
    char *pos;
    pos = strrchr( file_addr, '/' );
    pos = pos? pos + 1: file_addr;

    handler->file_dir = (char *)calloc( abs( pos - file_addr ) + 1, sizeof( char ) );
    if( handler->file_dir == NULL ) return -1;
    handler->file_name = (char *)calloc( strlen( pos ) + 1, sizeof( char ) );
    if( handler->file_name == NULL ) return -2;

    strcpy( handler->file_name, pos );

    handler->level = level == NULL? LOG_DEBUG: level;
    handler->max_line_size = DEFAULT_MAX_LINE_SIZE;
    handler->max_file_size = DEFAULT_MAX_FILE_SIZE;

    return 0;
}

int wm_logger_handler_destroy( wm_logger_handler_t *handler );

int wm_logger_handler_set_file_addr( wm_logger_handler_t *handler, char *file_addr );

int wm_logger_handler_set_level( wm_logger_handler_t *handler, unsigned int level );

int wm_logger_handler_set_line_size_max( wm_logger_handler_t *handler, unsigned int line_size_max );

int wm_logger_handler_set_file_size_max( wm_logger_handler_t *handler, unsigned int file_size_max );
