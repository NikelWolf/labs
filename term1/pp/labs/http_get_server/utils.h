#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int exist_file(const char *file_path);
int is_file_accessible(const char *file_path);
int is_file_readable(const char *file_path);
char *get_time();
unsigned short parse_ushort(const char *string);
int is_dir(const char *file_path);

#endif
