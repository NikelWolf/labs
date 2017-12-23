#define _GNU_SOURCE

#include "inet_utils.h"

static void *get_in_addr_struct(struct sockaddr *sa) {
    if(sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

char *get_client_addr_string(struct sockaddr_storage *client_addr) {
    char *addr_string = (char *) calloc(INET6_ADDRSTRLEN, sizeof(char));

    inet_ntop(client_addr->ss_family, get_in_addr_struct((struct sockaddr *) client_addr), addr_string, INET6_ADDRSTRLEN * sizeof(char));

    return addr_string;
}

char *read_message_from_client_to_separator(server_client *client, const char *sepatator) {
    char *line = "";
    char c;
    while(1) {
        if(recv(client->client_fd, &c, sizeof(char), 0) == -1) {
            log_error("error on recieving bytes from %s", client->addr);
            return NULL;
        }
        asprintf(&line, "%s%c", line, c);
        if(string_endswith(line, sepatator))
            break;
    }

    return line;
}

char *read_line_from_client(server_client *client) {
    return read_message_from_client_to_separator(client, "\n");
}

void send_message_to_client(server_client *client, const char *message) {
    int len = strlen(message);
    int writed_bytes = 0;
    while(len != 0) {
        if((writed_bytes = send(client->client_fd, message + strlen(message) - len, len, 0))) {
            if(writed_bytes == -1) {
                log_error("error on sending bytes to %s", client->addr);
                return;
            }
            len -= writed_bytes;
        }
    }
}

void send_file_to_client(server_client *client, const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if(file == NULL) {
        log_error("can not open %s", filepath);
        return;
    }
    while(!feof(file)) {
        char buffer[1024] = {0};
        fread(buffer, sizeof(char), 1023, file);
        send_message_to_client(client, buffer);
    }
    fclose(file);
}

static void sigchld_handler(int signal) {
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

int handle_dead_children_processes() {
    struct sigaction sa;
    sa.sa_handler = sigchld_handler; 
    sa.sa_flags = SA_RESTART;
    
    sigemptyset(&sa.sa_mask);
    
    if(sigaction(SIGCHLD, &sa, NULL) == -1) {
        log_error("error while setting handler for SIGCHLD signal");
        return 0;
    }

    return 1;
}
