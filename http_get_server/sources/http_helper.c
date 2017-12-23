#define _GNU_SOURCE

#include "http_helper.h"

void init_http_request(http_request *req) {
    req->method = 1;
    req->resource = NULL;
    req->request_fullness = 0;
    req->request_status = NULL;
    req->status_text = NULL;
}

http_request *create_http_request() {
    http_request *req = (http_request *) malloc(sizeof(http_request));

    init_http_request(req);

    return req;
}

void free_http_request(http_request *req) {
    if(req) {
        if(req->resource)
            free(req->resource);
        if(req->request_status)
            free(req->request_status);
        if(req->status_text)
            free(req->status_text);

        free(req);
    }
}

int get_string_request(char **string, server_client *client) {
    *string = read_message_from_client_to_separator(client, "\r\n\r\n");
    return 1;
}

http_request *parse_http_request(server_configs *sc, const char *string_request) {
    if(string_equal(string_request, "SHUTDOWN\r\n\r\n")) {
        return NULL;
    }

    http_request *req = create_http_request();
    if(string_find(string_request, "Host:") != -1) {
        char **request_lines = string_split(string_request, "\r\n", -1);
        if(string_array_length(request_lines) > 1) 
            req->request_fullness = 1;
        else 
            req->request_fullness = 0;
    
        char **main_part_of_request = string_split(request_lines[0], " ", -1);
        if(string_array_length(main_part_of_request) == 3 && string_find(main_part_of_request[2], "HTTP/") == -1) {
            string_free_splited_array(request_lines);
            string_free_splited_array(main_part_of_request);

            req->resource = sc->bad_request;
            req->request_status = strdup("400");
            req->status_text = strdup("Bad Request");

            return req;
        }
        char *method = main_part_of_request[0];
        char *resource = main_part_of_request[1];
        if(string_equal(method, "GET"))
            req->method = GET;
        else {
            string_free_splited_array(request_lines);
            string_free_splited_array(main_part_of_request);
            
            req->method = UNKNOWN;
            req->resource = sc->not_implemented;
            req->request_status = strdup("501");
            req->status_text = strdup("Not implemented");
            return req;
        }

        if(string_equal(resource, "/")) {
            req->resource = sc->standart;
            req->request_status = strdup("200");
            req->status_text = strdup("OK");
        } else {
            req->resource = string_concatate(sc->server_root, resource);

            if(exist_file(req->resource)) {
                if(!is_dir(req->resource)) {
                    if(!is_file_readable(req->resource)) {
                        free(req->resource);
    
                        req->resource = sc->forbidden;
                        req->request_status = strdup("403");
                        req->status_text = strdup("Forbidden");
                    } else {
                        req->request_status = strdup("200");
                        req->status_text = strdup("OK");
                    }
                } else {
                    free(req->resource);

                    req->resource = sc->not_implemented;
                    req->request_status = strdup("501");
                    req->status_text = strdup("Not implemented");                    
                }
            } else {
                free(req->resource);

                req->resource = sc->not_exist;
                req->request_status = strdup("404");
                req->status_text = strdup("Not Found");
            }

            string_free_splited_array(request_lines);
            string_free_splited_array(main_part_of_request);
        }
        
    } else {
        req->method = UNKNOWN;
        req->resource = sc->bad_request;
        req->request_status = strdup("400");
        req->status_text = strdup("Bad Request");
    }

    return req;
}

char *create_response_start_string(http_request *req) {
    char *start_text = "";
    asprintf(&start_text, "HTTP/1.1 %s %s\r\n\r\n", req->request_status, req->status_text);
    return start_text;
}

void send_response(server_client *client, http_request *req) {
    char *start_text = create_response_start_string(req);
    send_message_to_client(client, start_text);
    send_file_to_client(client, req->resource);
    send_message_to_client(client, "\r\n");
    free(start_text);
}