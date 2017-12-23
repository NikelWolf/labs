#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef struct server_client_s {
    int client_fd;
    char *addr;
} server_client;

#include "logger.h"
#include "inet_utils.h"
#include "configs_parser.h"

void init_server_client(server_client *client);
server_client *create_server_client();
void free_server_client(server_client *client);
int create_socket(int *sockfd, struct addrinfo *ai);
int set_socket_reusable(int sockfd);
int bind_socket(int sockfd, struct addrinfo *ai);
struct addrinfo *get_addrinfo_for_server(server_configs *sc);
int create_and_bind_and_listen_socket(int *sockfd, server_configs *sc);
int set_socket_listening(int sockfd, server_configs *sc);
int create_server_socket(server_configs *sc);
int close_socket(int sockfd);
server_client *get_client_from_connection(int sockfd);

#endif