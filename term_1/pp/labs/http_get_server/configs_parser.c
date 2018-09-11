#define _GNU_SOURCE

#include "configs_parser.h"

static void init_server_configs(server_configs *sc) {
    sc->shutdown_keyword = NULL;
    sc->log_file = NULL;

    sc->server_root = NULL;
    sc->standart = NULL;
    sc->not_exist = NULL;
    sc->forbidden = NULL;
    sc->bad_request = NULL;
    sc->not_implemented = NULL;

    sc->port = NULL;
    sc->backlog = NULL;
}

server_configs *create_server_configs() {
    server_configs *sc = (server_configs *) malloc(sizeof(server_configs));

    init_server_configs(sc);

    return sc;
}

void free_server_configs(server_configs *sc) {
    if(sc) {
        if(sc->shutdown_keyword)
            free(sc->shutdown_keyword);
        if(sc->log_file)
            free(sc->log_file);

        if(sc->server_root)
            free(sc->server_root);
        if(sc->standart)
            free(sc->standart);
        if(sc->not_exist)
            free(sc->not_exist);
        if(sc->forbidden)
            free(sc->forbidden);
        if(sc->bad_request)
            free(sc->bad_request);
        if(sc->not_implemented)
            free(sc->not_implemented);

        if(sc->port)
            free(sc->port);
        if(sc->backlog)
            free(sc->backlog);

        free(sc);
    }
}

void set_server_configs_field(server_configs *sc, ServerConfigsField field, const char *value) {
    switch(field) {
        case SHUTDOWN_KEYWORD: {
            sc->shutdown_keyword = strdup(value);
        }
        break;
        case LOG_FILE: {
            sc->log_file = strdup(value);
        }
        break;
        case SERVER_ROOT: {
            sc->server_root = strdup(value);
        }
        break;
        case STANDART: {
            sc->standart = strdup(value);
        }
        break;
        case NOT_EXIST: {
            sc->not_exist = strdup(value);
        }
        break;
        case FORBIDDEN: {
            sc->forbidden = strdup(value);
        }
        break;
        case BAD_REQUEST: {
            sc->bad_request = strdup(value);
        }
        break;
        case NOT_IMPLEMENTED: {
            sc->not_implemented = strdup(value);
        }
        break;
        case PORT: {
            sc->port = strdup(value);
        }
        break;
        case BACKLOG: {
            sc->backlog = strdup(value);
        }
        break;
    }
}

static int check_server_configs_completeness(server_configs *sc) {
    if( sc->shutdown_keyword == NULL ||
        sc->log_file == NULL ||
        sc->server_root == NULL ||
        sc->standart == NULL ||
        sc->not_exist == NULL ||
        sc->forbidden == NULL ||
        sc->bad_request == NULL ||
        sc->not_implemented == NULL ||
        sc->port == NULL ||
        sc->backlog == NULL )
            return 0;

    return 1;
}

static int check_if_empty(char **field) {
    if(string_is_empty(*field)) {
        free(*field);

        *field = strdup("[empty field]");

        return 1;
    }

    return 0;
}

static int check_and_exchange_path_if_need(char **field, int dir_check) {
    if(check_if_empty(field)) return 0;

    int result = 1;

    char *tmp;
    int exist = 0, readable = 0, dir = 0;
    if(!exist_file(*field)) exist = 1;
    else {
        if(dir_check && !is_dir(*field)) dir = 1;
        if(!dir_check && is_dir(*field)) dir = 1;
        if(!is_file_readable(*field)) readable = 1;
    }

    if(exist || readable || dir) {
        tmp = string_concatate(*field, exist ? "\t[not exist]" : dir_check && dir ? "\t[not directory]" : !dir_check && dir ? "\t[directory]" : readable ? "\t[not readable]" : "");
        free(*field);
        *field = tmp;
        result = 0;
    }

    return result;
}

static int check_and_exchange_decimal_if_need(char **field) {
    if(check_if_empty(field)) return 0;

    int result = 1;

    if(!string_is_decimal(*field)) {
        char *tmp = string_concatate(*field, "\t[not decimal]");
        free(*field);
        *field = tmp;

        result = 0;
    }

    return result;
}

static int check_and_exchange_log_file_if_need(char **field) {
    int result = 1;

    if(!string_is_empty(*field)) {
        if(exist_file(*field)) {
            if(is_file_accessible(*field)) {
                if(is_dir(*field)) {
                    char *tmp = string_concatate(*field, "\t[directory]");
                    free(*field);
                    *field = tmp;

                    result = 0;
                }
            } else {
                char *tmp = string_concatate(*field, "\t[not accessible]");
                free(*field);
                *field = tmp;

                result = 0;
            }
        }
    }

    return result;
}

static int check_server_configs_correctness(server_configs *sc) {
    int result;

    result = (
        check_and_exchange_path_if_need(&sc->server_root, 1) &
        check_and_exchange_path_if_need(&sc->standart, 0) &
        check_and_exchange_path_if_need(&sc->not_exist, 0) &
        check_and_exchange_path_if_need(&sc->forbidden, 0) &
        check_and_exchange_path_if_need(&sc->bad_request, 0) &
        check_and_exchange_path_if_need(&sc->not_implemented, 0) &
        check_and_exchange_decimal_if_need(&sc->port) &
        check_and_exchange_decimal_if_need(&sc->backlog) &
        check_and_exchange_log_file_if_need(&sc->log_file) &
        !check_if_empty(&sc->shutdown_keyword)
    );

    return result;
}

static void replace_server_configs_path_field_to_right(char **field) {
    if(!check_if_empty(field)) {
        const char *cur_dir = ".";
        const char *root_dir = "/";
        char *full_cur_dir;
        char *new_value;
        char *old_value;
        char *sc_value;
        char *tmp;

        full_cur_dir = tmp = getcwd(NULL, 0);
        full_cur_dir = string_concatate(tmp, "/");

        if(string_startswith(*field, cur_dir) || !string_startswith(*field, root_dir)) {
            if(string_startswith(*field, cur_dir))
                sc_value = string_slice(*field, 1, -1);
            else if(!string_startswith(*field, root_dir))
                sc_value = string_copy(*field);
            else
                sc_value = string_copy("");


            old_value = *field;
            new_value = string_concatate(full_cur_dir, sc_value);

            *field = strdup(new_value);

            free(sc_value);
            free(old_value);
            free(new_value);
        }

        free(tmp);
        free(full_cur_dir);
    }
}

static void exchange_server_configs_values_to_right(server_configs *sc) {
    if(!string_is_empty(sc->log_file))
        replace_server_configs_path_field_to_right(&sc->log_file);
    else {
        free(sc->log_file);
        sc->log_file = strdup("http_server_log.log");
        replace_server_configs_path_field_to_right(&sc->log_file);
    }

    replace_server_configs_path_field_to_right(&sc->server_root);
    replace_server_configs_path_field_to_right(&sc->standart);
    replace_server_configs_path_field_to_right(&sc->not_exist);
    replace_server_configs_path_field_to_right(&sc->forbidden);
    replace_server_configs_path_field_to_right(&sc->bad_request);
    replace_server_configs_path_field_to_right(&sc->not_implemented);
}

char *server_configs_to_string(server_configs *sc) {
    char *msg;
    asprintf(&msg,
            "server configuration:\n\t"
            "shutdown keyword: %s\n\t"
            "log file: %s\n\t"
            "server root: %s\n\t"
            "standart page: %s\n\t"
            "not existing page: %s\n\t"
            "forbidden page: %s\n\t"
            "bad request page: %s\n\t"
            "not implemented page: %s\n\t"
            "port for binding server: %s\n\t"
            "backlog for server: %s\n\n",
            sc && sc->shutdown_keyword ? sc->shutdown_keyword : "error",
            sc && sc->log_file ? sc->log_file : "error",
            sc && sc->server_root ? sc->server_root : "error",
            sc && sc->standart ? sc->standart : "error",
            sc && sc->not_exist ? sc->not_exist : "error",
            sc && sc->forbidden ? sc->forbidden : "error",
            sc && sc->bad_request ? sc->bad_request : "error",
            sc && sc->not_implemented ? sc->not_implemented : "error",
            sc && sc->port ? sc->port : "error",
            sc && sc->backlog ? sc->backlog : "error" );
    return msg;
}

int parse_server_configs_file(server_configs **configs, FILE *configuration_file) {
    *configs = NULL;

    server_configs *sc = create_server_configs();

    while(!feof(configuration_file)) {
        char *line = NULL;
        size_t line_size = 0;

        if(getline(&line, &line_size, configuration_file) == -1 && errno) {
            fprintf(stderr, "error on reading line from configuration file: %s\n", strerror(errno));

            free_server_configs(sc);

            return 0;
        }

        char **splited_line = string_split(line, "=", 2);

        free(line);

        char *key;
        char *value;

        if(string_array_length((const char **) splited_line) != 2 && !feof(configuration_file)) {
            string_free_splited_array(splited_line);

            continue;
        } else if(string_array_length((const char **) splited_line) == 1 && feof(configuration_file)) {
            key = string_lrstrip(splited_line[0]);
            value = "";
        } else {
            key = string_lrstrip(splited_line[0]);
            value = string_lrstrip(splited_line[1]);
        }

        string_free_splited_array(splited_line);

        if(string_equal(key, "shutdown_keyword")) {
            set_server_configs_field(sc, SHUTDOWN_KEYWORD, value);
        } else if(string_equal(key, "log_name")) {
            set_server_configs_field(sc, LOG_FILE, value);
        } else if(string_equal(key, "server_root")) {
            set_server_configs_field(sc, SERVER_ROOT, value);
        } else if(string_equal(key, "standart")) {
            set_server_configs_field(sc, STANDART, value);
        } else if(string_equal(key, "not_exist")) {
            set_server_configs_field(sc, NOT_EXIST, value);
        } else if(string_equal(key, "forbidden")) {
            set_server_configs_field(sc, FORBIDDEN, value);
        } else if(string_equal(key, "bad_request")) {
            set_server_configs_field(sc, BAD_REQUEST, value);
        } else if(string_equal(key, "not_implemented")) {
            set_server_configs_field(sc, NOT_IMPLEMENTED, value);
        } else if(string_equal(key, "port")) {
            set_server_configs_field(sc, PORT, value);
        } else if(string_equal(key, "backlog")) {
            set_server_configs_field(sc, BACKLOG, value);
        }

        free(key);
        free(value);
    }

    if(!check_server_configs_completeness(sc)) {
        *configs = sc;

        return 0;
    }

    exchange_server_configs_values_to_right(sc);

    if(!check_server_configs_correctness(sc)) {

        *configs = sc;

        return 0;
    }

    *configs = sc;
    return 1;
}

int parse_server_configs_with_filename(server_configs **configs, const char *file_path) {
    if(!exist_file(file_path)) {
        fprintf(stderr, "file does not exist: %s\n", file_path);

        return 0;
    } else {
        if(!is_file_readable(file_path)) {
            fprintf(stderr, "file is not readable: %s\n", file_path);

            return 0;
        }
    }

    FILE *configuration_file = fopen(file_path, "r");
    if(configuration_file == NULL) {
        fprintf(stderr, "error on opening configuration file: %s\nerror: %s\n", file_path, strerror(errno));

        return 0;
    }

    if(!parse_server_configs_file(configs, configuration_file)) {
        fprintf(stderr, "error on parsing configurations for server\n");
        char *strsc = server_configs_to_string(*configs);
        fprintf(stderr, "%s\n", strsc);
        free(strsc);

        if(fclose(configuration_file) == EOF) {
            fprintf(stderr, "error on closing configuration file: %s\nerror: %s\n", file_path, strerror(errno));

            return 0;
        }


        return 0;
    }

    if(fclose(configuration_file) == EOF) {
        fprintf(stderr, "error on closing configuration file: %s\nerror: %s\n", file_path, strerror(errno));

        return 0;
    }

    return 1;
}
