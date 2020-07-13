/*
 * @Author: llseng 
 * @Date: 2020-07-08 15:47:35 
 * @Last Modified by: llseng
 * @Last Modified time: 2020-07-13 16:12:58
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

#define DEFAULT_MAX_LINE_SIZE 8192
#define DEFAULT_MAX_FILE_SIZE 104857600

#define WRITE_COUNT_MOD 100

typedef struct wm_logger_handler {
    FILE *fd;
    char *file_dir;
    char *file_name;
    unsigned int level;
    unsigned int max_line_size;
    unsigned int max_file_size;
    unsigned int write_count;
} wm_logger_handler_t;

typedef struct wm_logger {
    char *name;
    unsigned int handler_len;
    wm_logger_handler_t **handler_arr;
} wm_logger_t;

int wm_logger_init( wm_logger_t *logger, char *name );

int wm_logger_destroy( wm_logger_t *logger );

int wm_logger_set_name( wm_logger_t *logger, char *name );

int wm_logger_add_handler( wm_logger_t *logger, wm_logger_handler_t *handler );

int wm_logger_pop_handler( wm_logger_t *logger );

int wm_logger_write( wm_logger_t *logger, int level, char *fmt, ... );

int wm_logger_handler_init( wm_logger_handler_t *handler, char *file_addr, unsigned int level );

int wm_logger_handler_destroy( wm_logger_handler_t *handler );

int wm_logger_handler_set_file_addr( wm_logger_handler_t *handler, char *file_addr );

int wm_logger_handler_set_level( wm_logger_handler_t *handler, unsigned int level );

int wm_logger_handler_set_max_line_size( wm_logger_handler_t *handler, unsigned int max_line_size );

int wm_logger_handler_set_max_file_size( wm_logger_handler_t *handler, unsigned int max_file_size );

int wm_logger_handler_write( wm_logger_handler_t *handler, unsigned int level, char *message );

int wm_get_level_name( unsigned int level, char *str );

int wm_logger_get_name( wm_logger_t *logger, char *str);

int wm_logger_handler_get_file_addr( wm_logger_handler_t *handler, char *str );

#define wm_log_debug( logger, fmt, ... ) wm_logger_write( logger, LOG_DEBUG, fmt, ##__VA_ARGS__ )
#define wm_log_info( logger, fmt, ... ) wm_logger_write( logger, LOG_INFO, fmt, ##__VA_ARGS__ )
#define wm_log_notice( logger, fmt, ... ) wm_logger_write( logger, LOG_NOTICE, fmt, ##__VA_ARGS__ )
#define wm_log_warning( logger, fmt, ... ) wm_logger_write( logger, LOG_WARNING, fmt, ##__VA_ARGS__ )
#define wm_log_warn( logger, fmt, ... ) wm_logger_write( logger, LOG_WARNING, fmt, ##__VA_ARGS__ )
#define wm_log_error( logger, fmt, ... ) wm_logger_write( logger, LOG_ERROR, fmt, ##__VA_ARGS__ )
#define wm_log_critical( logger, fmt, ... ) wm_logger_write( logger, LOG_CRITICAL, fmt, ##__VA_ARGS__ )

#endif /*_WM_LOGGER_H_*/