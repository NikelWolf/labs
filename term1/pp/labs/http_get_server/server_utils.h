#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <netdb.h>
#include <sys/socket.h>

#include "configs_parser.h"

void exit_handler();
void sigterm_handler(int signal);
void sigchld_handler(int signal);
void set_signal_handler(int signal, void (*handler)(int));
int read_request(int sfd, char **request);
int send_file(int sfd, const char *filename);
int response_for_http_request(int sfd, const char *http_head, size_t http_head_len, const char *filename);
char *get_client_ip(struct sockaddr *client_addr);
int handle_request(int client_fd, struct sockaddr_storage *client_addr, server_configs *sc);
int init_server(int *server_fd, server_configs *sc);
void start_server(server_configs *sc);

#endif
