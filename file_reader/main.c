#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int exist_file(const char *filepath) {
    struct stat st;
    if(stat(filepath, &st) == -1) {
        return 0;
    } else {
        return 1;
    }
}

unsigned long int get_file_size(const char *filepath) {
    struct stat st;
    stat(filepath, &st);
    return st.st_size;
}


int main(int argc, char *argv[]) {
    if(argc < 2 || argc > 3) {
        fprintf(stderr, "usage: package_reader [mode] data_file\n");
        exit(EXIT_FAILURE);
    }

    const char *mode = "r";
    char *filename = strdup(argv[1]);
    if(argc == 3) {
        free(filename);
        filename = strdup(argv[2]);
        
        if(!strcmp(argv[1], "binary")) {
            printf("binary mode\n");
            mode = "rb";
        } else if(strcmp(argv[1], "normal")) {
            printf("unrecognized option %s\nmode set to normal(r)\n", argv[1]);
        }
    }

    while(!exist_file(filename)) {
        free(filename);

        printf("enter right filepath: ");

        char *line = NULL;
        size_t size = 0;
        size_t readed_bytes = getline(&line, &size, stdin);

        line[readed_bytes-1] = '\0';
        filename = line;
    }
    
    FILE *file = fopen(filename, mode);
    if(file == NULL) {
        fprintf(stderr, "error on opening %s: %s|\t(%d)", filename, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }

    if(!strcmp(mode, "r")) {
        while(!feof(file)) {
            char *line = NULL;
            size_t size = 0;
            getline(&line, &size, file);
            
            printf("%s", line);
            
            free(line);
        }
    } else {
        while(!feof(file)) {
            unsigned char buffer[1024];
            size_t readed_bytes = fread(buffer, sizeof(unsigned char), 1024, file);

            size_t i;
            for(i = 0; i < readed_bytes; i++) {
                if(i % 16 == 0) {
                    printf("\n");
                }
                if(i % 2 == 0) {
                    printf("\t");
                }
                printf("%02x", buffer[i]);
            }
        }
    }

    free(filename);
    printf("\n");

    return 0;
}