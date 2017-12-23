#include "server_utils.h"

void init_server_client(server_client *client) {
    client->client_fd = -1;
    client->addr = NULL;
}

server_client *create_server_client() {
    server_client *client = (server_client *) malloc(sizeof(server_client));

    init_server_client(client);

    return client;
}

void free_server_client(server_client *client) {
    if(client) {
        if(client->addr)
            free(client->addr);
    
        if(!close(client->client_fd))
            log_error("error on closing client socket: %s", strerror(errno));

        free(client);
    }
}

int create_socket(int *sockfd, struct addrinfo *ai) {
    if((*sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) == -1) {
        *sockfd = -1;

        log_error("error on creating socket: %s", strerror(errno));
        return 0;
    }
    
    return 1;
}

int set_socket_reusable(int sockfd) {
    int yes = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        log_error("error on calling setsockopt on socket: %s", strerror(errno));
        return 0;
    }
    
    return 1;
}

int bind_socket(int sockfd, struct addrinfo *ai) {
    if(bind(sockfd, ai->ai_addr, ai->ai_addrlen) == -1) {
        log_error("error on binding socket: %s", strerror(errno));
        return 0;
    }
    
    return 1;
}

int set_socket_listening(int sockfd, server_configs *sc) {
    if(listen(sockfd, (int) parse_ushort(sc->backlog)) == -1) {
        return 0;
    }
    
    return 1;
}

struct addrinfo *get_addrinfo_for_server(server_configs *sc) {
    struct addrinfo hints, *ai;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    if((errno = getaddrinfo(NULL, sc->port, &hints, &ai)) != 0) {
        return NULL;
    }

    return ai;
}

int create_and_bind_and_listen_socket(int *sockfd, server_configs *sc) {
    struct addrinfo *ai_pointer, *ai;
    if((ai = get_addrinfo_for_server(sc)) == NULL) {
        log_error("error while getting address info: %s", gai_strerror(errno));
        
        return 0;
    }

    for(ai_pointer = ai; ai_pointer; ai_pointer = ai_pointer->ai_next) {
        if(!create_socket(sockfd, ai_pointer)) {
            continue;
        }
        
        if(!set_socket_reusable(*sockfd)) {
            close(*sockfd);
            *sockfd = -1;
            
            return 0;
        }

        if(!bind_socket(*sockfd, ai_pointer)) {
            close(*sockfd);

            continue;
        }

        break;
    }

    if(ai_pointer == NULL) {
        log_error("failed to bind socket");

        freeaddrinfo(ai);
        *sockfd = -1;

        return 0;
    }

    freeaddrinfo(ai);

    if(!set_socket_listening(*sockfd, sc)) {
        log_error("error on listening socket: %s", strerror(errno));        

        close(*sockfd);
        *sockfd = -1;

        return 0;
    }

    return 1;
}

int create_server_socket(server_configs *sc) {
    int sockfd = -1;

    create_and_bind_and_listen_socket(&sockfd, sc);

    return sockfd;
}

int close_socket(int sockfd) {
    if(close(sockfd) == -1 && errno) {
        log_error("error while closing socket: %s", strerror(errno));
        
        return 0;
    }

    return 1;
}


server_client *get_client_from_connection(int sockfd) {
    server_client *client = create_server_client();

    while(1) {
        struct sockaddr_storage client_addr;
        socklen_t sock_size = sizeof(struct sockaddr_storage);
        int fd;
        if((fd = accept(sockfd, (struct sockaddr *) &client_addr, &sock_size)) == -1) {
            log_error("can not accept client");
            continue;
        }

        client->client_fd = fd;
        client->addr = get_client_addr_string(&client_addr);

        break;
    }

    return client;
}