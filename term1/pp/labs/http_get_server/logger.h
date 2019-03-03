#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>

#include "utils.h"

void init_logger(const char *filename);
void close_logger();
void log_msg(const char *message, ...);
void log_error(const char *message, ...);
void log_client_connection(const char *client_ip);
void log_client_disconnection(const char *client_ip);
void log_request(const char *client_ip, const char *request);
void log_response(const char *client_ip, const char *response);
void log_shutdown();
void log_server_start();

#endif
