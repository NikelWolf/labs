#define _GNU_SOURCE

#include "utils.h"

int exist_file(const char *file_path) {
    if(!access(file_path, F_OK))
        return 1;

    return 0;
}

int is_file_accessible(const char *file_path) {
    if(!access(file_path, R_OK | W_OK))
        return 1;

    return 0;
}

int is_file_readable(const char *file_path) {
    if(!access(file_path, W_OK))
        return 1;

    return 0;
}

char *get_time() {
    time_t timer = time(NULL);
    char *time_string = strdup(ctime(&timer));
    time_string[strlen(time_string)-1] = '\0';

    return time_string;
}

unsigned short parse_ushort(const char *string) {
    return (unsigned short) strtol(string, (char **) NULL, 10);
}

int is_dir(const char *file_path) {
    struct stat st;
    if(stat(file_path, &st))
        return 0;

    return S_ISDIR(st.st_mode);
}
