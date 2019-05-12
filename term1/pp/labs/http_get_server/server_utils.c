#define _GNU_SOURCE

#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "configs_parser.h"
#include "logger.h"

#include "server_utils.h"

extern int err;
extern server_configs *sc;

void exit_handler() {
    if (sc)
        free_server_configs(sc);

    close_logger();
}

void sigterm_handler(int signal) {
    signal++;

    log_shutdown();
    exit(EXIT_SUCCESS);
}

void sigchld_handler(int signal) {
    signal++;

    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

void set_signal_handler(int signal, void (*handler)(int)) {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(signal, &sa, NULL) == -1) {
        err = errno;
        log_error("sigaction: %s", strerror(err));
        exit(EXIT_FAILURE);
    }
}

int read_request(int sfd, char **request) {
    *request = "";

    while (1) {
        char buffer[1025];
        memset(buffer, 0, 1025);

        int readed_bytes = recv(sfd, buffer, 1024, 0);
        if (readed_bytes == -1) {
            err = errno;
            log_error("recv: %s", strerror(err));
            return 0;
        }

        asprintf(request, "%s%s", *request, buffer);

        if (strlen(*request) >= 4) {
            if (strncmp(*request + strlen(*request) - 4, "\r\n\r\n", 4) == 0) {
                break;
            }
        }
    }

    return 1;
}

int send_file(int sfd, const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        err = errno;
        log_error("open: %s", strerror(err));
        return 0;
    }

    while (1) {
        char buffer[1025];
        memset(buffer, 0, 1025);

        int readed_bytes = read(fd, buffer, 1024);
        if (readed_bytes == -1) {
            err = errno;
            log_error("read: %s", strerror(err));
            return 0;
        } else if (readed_bytes == 0) {
            break;
        }

        int sended_bytes = send(sfd, buffer, readed_bytes, 0);
        if (sended_bytes == -1) {
            err = errno;
            log_error("send: %s", strerror(err));
            return 0;
        }
    }

    close(fd);

    return 1;
}

int response_for_http_request(int sfd, const char *http_head, size_t http_head_len, const char *filename) {
    int sended_bytes = send(sfd, http_head, http_head_len, 0);
    if (sended_bytes == -1) {
        err = errno;
        log_error("send: %s", strerror(err));
        return 0;
    }

    if (send_file(sfd, filename) == 0) {
        log_error("send_file");
        return 0;
    }

    sended_bytes = send(sfd, "\r\n\r\n", 4, 0);
    if (sended_bytes == -1) {
        log_error("send");
        return 0;
    }

    return 1;
}

char *get_client_ip(struct sockaddr *client_addr) {
    char *ip_str;
    if (client_addr->sa_family == AF_INET) {
        struct sockaddr_in *client_addr_in = (struct sockaddr_in *)client_addr;
        ip_str = (char *)calloc(INET_ADDRSTRLEN, sizeof(char));
        inet_ntop(AF_INET, client_addr_in, ip_str, INET_ADDRSTRLEN);
    } else {
        struct sockaddr_in6 *client_addr_in6 = (struct sockaddr_in6 *)client_addr;
        ip_str = (char *)calloc(INET6_ADDRSTRLEN, sizeof(char));
        inet_ntop(AF_INET6, client_addr_in6, ip_str, INET6_ADDRSTRLEN);
    }

    return ip_str;
}

int handle_request(int client_fd, struct sockaddr_storage *client_addr, server_configs *sc) {
    char *client_ip = get_client_ip((struct sockaddr *)client_addr);
    log_client_connection(client_ip);

    char *request = "";
    if (read_request(client_fd, &request) == 0) {
        log_error("read_request");
        free(client_ip);
        free(request);
        return 0;
    }

    if (strncmp(request, sc->shutdown_keyword, strlen(sc->shutdown_keyword)) == 0) {
        free(client_ip);
        free(request);
        kill(getppid(), SIGTERM);
        return 1;
    }

    char **request_head = string_split(request, "\r\n", 1);
    if (string_array_length((const char **)request_head) >= 1) {
        log_request(client_ip, request_head[0]);
    } else {
        log_request(client_ip, "[]");
    }
    string_free_splited_array(request_head);

    char *path = "";
    char *http_header = "";
    char *log_http_header = "";
    size_t http_header_size = 0;
    char *request_head_parts[3] = {0};
    request_head_parts[0] = strtok(request, " \t\n");
    if (strncmp(request_head_parts[0], "GET\0", 4) == 0) {
        request_head_parts[1] = strtok(NULL, " \t");
        request_head_parts[2] = strtok(NULL, " \t\n");
        if (strncmp(request_head_parts[2], "HTTP/1.0", 8) != 0 && strncmp(request_head_parts[2], "HTTP/1.1", 8) != 0) {
            log_http_header = "HTTP/1.0 400 Bad Request";
            http_header = "HTTP/1.0 400 Bad Request\r\n\r\n";
            http_header_size = 28;
            asprintf(&path, "%s", sc->bad_request);
        } else {
            if (strncmp(request_head_parts[1], "/\0", 2) == 0) {
                asprintf(&path, "%s", sc->standart);
            } else {
                asprintf(&path, "%s%s", sc->server_root, request_head_parts[1]);
            }

            if (exist_file(path)) {
                if (is_file_accessible(path)) {
                    log_http_header = "HTTP/1.0 200 OK";
                    http_header = "HTTP/1.0 200 OK\r\n\r\n";
                    http_header_size = 19;
                } else {
                    log_http_header = "HTTP/1.0 403 Forbidden";
                    http_header = "HTTP/1.0 403 Forbidden\r\n\r\n";
                    http_header_size = 26;
                    asprintf(&path, "%s", sc->forbidden);
                }
            } else {
                log_http_header = "HTTP/1.0 404 Not Found";
                http_header = "HTTP/1.0 404 Not Found\r\n\r\n";
                http_header_size = 26;
                asprintf(&path, "%s", sc->not_exist);
            }
        }
    } else {
        log_http_header = "HTTP/1.0 501 Not Implemented";
        http_header = "HTTP/1.0 501 Not Implemented\r\n\r\n";
        http_header_size = 32;
        asprintf(&path, "%s", sc->not_implemented);
    }

    if (response_for_http_request(client_fd, http_header, http_header_size, path) == 0) {
        log_error("response_for_http_request");
        free(request);
        free(path);
        free(client_ip);
        return 0;
    } else {
        char *tmp_str;
        asprintf(&tmp_str, "head: [%s]; file: [%s]", log_http_header, path);
        log_response(client_ip, tmp_str);
        free(tmp_str);
    }

    free(request);
    free(path);
    free(client_ip);

    return 1;
}

int init_server(int *server_fd, server_configs *sc) {
    struct addrinfo hints, *ai, *p;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int gai_status = getaddrinfo(NULL, sc->port, &hints, &ai);
    if (gai_status != 0) {
        freeaddrinfo(ai);
        log_error("getaddrinfo: %s\n", gai_strerror(gai_status));
        return 0;
    }

    for (p = ai; p != NULL; p = p->ai_next) {
        *server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (*server_fd == -1) {
            err = errno;
            log_error("socket: %s", strerror(err));
            continue;
        }

        int yes = 1;
        if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            err = errno;
            log_error("setsockopt: %s", strerror(err));
            freeaddrinfo(ai);
            return 0;
        }

        if (bind(*server_fd, p->ai_addr, p->ai_addrlen) == -1) {
            err = errno;
            log_error("bind: %s", strerror(err));
            continue;
        }

        break;
    }

    freeaddrinfo(ai);

    if (p == NULL) {
        log_error("failed to bind server");
        return 0;
    }

    if (listen(*server_fd, parse_ushort(sc->backlog)) == -1) {
        err = errno;
        log_error("listen: %s", strerror(err));
        return 0;
    }

    return 1;
}

void start_server(server_configs *sc) {
    int server_fd;
    if (init_server(&server_fd, sc) == 0) {
        exit(EXIT_FAILURE);
    }

    log_server_start();
    char *sc_str = server_configs_to_string(sc);
    log_msg("\n%s", sc_str);
    free(sc_str);

    set_signal_handler(SIGCHLD, sigchld_handler);

    while (1) {
        struct sockaddr_storage client_addr;
        socklen_t client_addr_size = sizeof(struct sockaddr_storage);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_size);

        if (client_fd == -1) {
            err = errno;
            log_error("accept: %s", strerror(err));
            continue;
        }

        pid_t pid = fork();
        if (pid == -1) {
            err = errno;
            log_error("fork: %s", strerror(err));
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            close(server_fd);
            if (handle_request(client_fd, &client_addr, sc) == 0) {
                log_error("handle_request");
                exit(EXIT_FAILURE);
            }
            close(client_fd);
            exit(EXIT_SUCCESS);
        } else {
            close(client_fd);
        }
    }
}
