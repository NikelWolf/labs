#define _GNU_SOURCE

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "configs_parser.h"
#include "logger.h"
#include "server_utils.h"

int err;
server_configs *sc = NULL;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: http_get_server configuration.ini\n");
        exit(EXIT_FAILURE);
    }

    atexit(exit_handler);
    set_signal_handler(SIGTERM, sigterm_handler);

    if (parse_server_configs_with_filename(&sc, argv[1]) == 0) {
        exit(EXIT_FAILURE);
    }

    init_logger(sc->log_file);

    pid_t pid = fork();
    if (pid == -1) {
        err = errno;
        log_error("fork: %s", strerror(err));
    } else if (pid == 0) {
        start_server(sc);
    } else {
        printf("server starded with pid %d on port %s and root %s\n", pid, sc->port, sc->server_root);
    }

    return 0;
}
