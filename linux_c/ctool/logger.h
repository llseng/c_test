/*
 * @Author: llseng 
 * @Date: 2020-07-08 15:47:35 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-09 16:10:59
 */
#ifndef _WM_LOGGER_H_
#define _WM_LOGGER_H_

#include <stdio.h>

/*日志等级*/

#define LOG_DEBUG       0x1
#define LOG_INFO        0x2
#define LOG_NOTICE      0x4
#define LOG_WARNING     0x8
#define LOG_ERROR       0x10
#define LOG_CRITICAL    0x20

typedef struct wm_logger {
    char *name;
    int handler_len;
    wm_logger_handler_t **handler_arr;
} wm_logger_t;

typedef struct wm_logger_handler {
    FILE *fd;
    char *file_dir;
    char *file_name;
    unsigned int level;
    unsigned int line_size_max;
    unsigned int file_size_max;
} wm_logger_handler_t;

int wm_logger_init( wm_logger_t *logger, char *name );

int wm_logger_destroy( wm_logger_t *logger );

int wm_logger_set_name( wm_logger_t *logger, char *name );

int wm_logger_add_handler( wm_logger_t *logger, wm_logger_handler_t *handler );

int wm_logger_pop_handler( wm_logger_t *logger );

int wm_logger_write( wm_logger_t *logger, int level, ... );

int wm_logger_handler_init( wm_logger_handler_t *handler, char *file_addr, unsigned int level );

int wm_logger_handler_destroy( wm_logger_handler_t *handler );

int wm_logger_handler_set_file_addr( wm_logger_handler_t *handler, char *file_addr );

int wm_logger_handler_set_level( wm_logger_handler_t *handler, unsigned int level );

int wm_logger_handler_set_line_size_max( wm_logger_handler_t *handler, unsigned int line_size_max );

int wm_logger_handler_set_file_size_max( wm_logger_handler_t *handler, unsigned int file_size_max );

#define wm_log_debug( logger, ... ) wm_logger_write( logger, LOG_DEBUG, ... )
#define wm_log_info( logger, ... ) wm_logger_write( logger, LOG_INFO, ... )
#define wm_log_notice( logger, ... ) wm_logger_write( logger, LOG_NOTICE, ... )
#define wm_log_warning( logger, ... ) wm_logger_write( logger, LOG_WARNING, ... )
#define wm_log_warn( logger, ... ) wm_logger_write( logger, LOG_WARNING, ... )
#define wm_log_error( logger, ... ) wm_logger_write( logger, LOG_ERROR, ... )
#define wm_log_critical( logger, ... ) wm_logger_write( logger, LOG_CRITICAL, ... )

#endif /*_WM_LOGGER_H_*/