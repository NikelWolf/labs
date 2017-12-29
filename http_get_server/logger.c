#define _GNU_SOURCE

#include "logger.h"

static FILE *log_file = NULL;
static int init_completed = 0;

void init_logger(const char *filename) {
    if(init_completed) {
        close_logger();
        init_completed = 0;
    }

    char *mode;

    if(!exist_file(filename)) {
        fprintf(stderr, "%s file does not exist\ncreating new file\n", filename);
        mode = "w";
    } else {
        if(!is_file_accessible(filename)) {
            fprintf(stderr, "%s file is not accessible\ncan not create log file, exit\n", filename);
            exit(EXIT_FAILURE);
        }
        mode = "a";
    }

    if((log_file = fopen(filename, mode)) == NULL) {
        fprintf(stderr, "can not open %s\nerror: %s\nexiting", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }

    init_completed = 1;
}

void close_logger() {
    if(!init_completed) return;

    fclose(log_file);
}

void log_msg(const char *message, ...) {
    if(!init_completed) return;

    va_list vl;
    char *time_string = get_time();
    char *log_message = "";

    va_start(vl, message);
    vasprintf(&log_message, message, vl);
    va_end(vl);

    fprintf(log_file, "[(time: %25s)|(type: %15s)] => { %s }\n", time_string, "message", log_message);
    fflush(log_file);

    free(time_string);
    free(log_message);
}

void log_error(const char *message, ...) {
    if(!init_completed) return;

    va_list vl;
    char *time_string = get_time();
    char *log_message = "";

    va_start(vl, message);
    vasprintf(&log_message, message, vl);
    va_end(vl);

    fprintf(log_file, "[(time: %25s)|(type: %15s)] => { %s }\n", time_string, "ERROR", log_message);
    fflush(log_file);

    free(time_string);
    free(log_message);
}

void log_client_connection(const char *client_ip) {
    if(!init_completed) return;

    char *time_string = get_time();
    fprintf(log_file, "[(time: %25s)|(type: %15s)] => { connection from [%s] }\n", time_string, "connection", client_ip);
    fflush(log_file);

    free(time_string);
}

void log_client_disconnection(const char *client_ip) {
    if(!init_completed) return;

    char *time_string = get_time();
    fprintf(log_file, "[(time: %25s)|(type: %15s)] => { [%s] disconnected }\n", time_string, "disconnection", client_ip);
    free(time_string);
}

void log_request(const char *client_ip, const char *request) {
    if(!init_completed) return;

    char *time_string = get_time();
    fprintf(log_file, "[(time: %25s)|(type: %15s)] => { request: |%s| from [%s] }\n", time_string, "request", request, client_ip);
    free(time_string);
}

void log_response(const char *client_ip, const char *response) {
    if(!init_completed) return;

    char *time_string = get_time();
    fprintf(log_file, "[(time: %25s)|(type: %15s)] => { response: |%s| to [%s] }\n", time_string, "response", response, client_ip);
    free(time_string);
}

void log_shutdown() {
    if(!init_completed) return;

    char *time_string = get_time();
    fprintf(log_file, "[(time: %25s)|(type: %15s)] => { server shutdown }\n\n\n\n", time_string, "shutdown");
    fflush(log_file);

    free(time_string);
}

void log_server_start() {
    if(!init_completed) return;

    char *time_string = get_time();
    fprintf(log_file, "[(time: %25s)|(type: %15s)] => { start server }\n\n", time_string, "starting");
    fflush(log_file);

    free(time_string);
}
