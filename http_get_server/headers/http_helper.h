#ifndef HTTP_HELPER_H
#define HTTP_HELPER_H

#include <stdlib.h>

typedef enum http_methods_e {GET, UNKNOWN} http_method;

typedef struct http_request_s {
    http_method method;
    char *resource;
    int request_fullness;
    char *request_status;
    char *status_text;
} http_request;

#include "configs_parser.h"
#include "server_utils.h"

void init_http_request(http_request *req);
http_request *create_http_request();
void free_http_request(http_request *req);
int get_string_request(char **string, server_client *client);
http_request *parse_http_request(server_configs *sc, const char *string_request);
char *create_response_start_string(http_request *req);
void send_response(server_client *client, http_request *req);

#endif