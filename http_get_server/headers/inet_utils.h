#ifndef INET_UTILS_H
#define INET_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>

#include "logger.h"
#include "server_utils.h"
#include "string_worker.h"

char *get_client_addr_string(struct sockaddr_storage *client_addr);
char *read_line_from_client(server_client *client);
char *read_message_from_client_to_separator(server_client *client, const char *sepatator);
void send_message_to_client(server_client *client, const char *message);
void send_file_to_client(server_client *client, const char *filepath);
int handle_dead_children_processes();


#endif