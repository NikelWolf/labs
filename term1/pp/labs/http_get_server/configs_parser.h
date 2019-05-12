#ifndef CONFIGS_PARSER_H
#define CONFIGS_PARSER_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct server_configs_s {
    char *shutdown_keyword;
    char *log_file;
    char *server_root;
    char *standart;
    char *not_exist;
    char *forbidden;
    char *bad_request;
    char *not_implemented;
    char *port;
    char *backlog;
} server_configs;

typedef enum ServerConfigsField_e {
    SHUTDOWN_KEYWORD,
    LOG_FILE,
    SERVER_ROOT,
    STANDART,
    NOT_EXIST,
    FORBIDDEN,
    BAD_REQUEST,
    NOT_IMPLEMENTED,
    PORT,
    BACKLOG
} ServerConfigsField;

#include "string_worker.h"
#include "utils.h"

server_configs *create_server_configs();
void free_server_configs(server_configs *sc);
void set_server_configs_field(server_configs *sc, ServerConfigsField field, const char *value);
int parse_server_configs_file(server_configs **configs, FILE *configuration_file);
int parse_server_configs_with_filename(server_configs **configs, const char *file_path);
char *server_configs_to_string(server_configs *sc);

#endif
