#include <stdio.h>
#include <stdlib.h>

#include "configs_parser.h"
#include "logger.h"
#include "server_utils.h"
#include "string_worker.h"
#include "http_helper.h"


int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "usage: http_server configurations_file\n");
        exit(EXIT_FAILURE);
    }

    server_configs *sc;
    
    if(!parse_server_configs_with_filename(&sc, argv[1])) {
        char *str_sc = server_configs_to_string(sc);
        fprintf(stderr, "%s\n", str_sc);

        free(str_sc);
        free_server_configs(sc);
        
        exit(EXIT_FAILURE);
    }
    
    init_logger(sc->log_file);
    
    char *str_sc = server_configs_to_string(sc);
    log_msg("server configuration was readed\n%s", str_sc);
    free(str_sc);
    
    int server_socket;

    if(!(server_socket = create_server_socket(sc))) {
        close_logger();
        free_server_configs(sc);

        exit(EXIT_FAILURE);
    }

    // if(!fork()) {
    //     printf("forked\n");
    //     execl("python", "python", "socket_sender.py", NULL); // run simple helper script
    // }

    server_client *client = get_client_from_connection(server_socket); //TODO
    printf("client accepted\n");
    char *client_addr = string_copy(client->addr);

    log_client_connection(client_addr);

    char *string_request = NULL;
    if(!get_string_request(&string_request, client)) { //TODO
        log_error("can not accept request from %s", client_addr);
    } else {
        log_request(client_addr, string_request);
    }

    free_server_client(client);
    
    log_client_disconnection(client_addr);

    free(client_addr);
    if(string_request) 
        free(string_request);

    if(!close_socket(server_socket)) {        
        close_logger();
        free_server_configs(sc);

        exit(EXIT_FAILURE);
    }

    close_logger();
    free_server_configs(sc);
    
    return 0;
}