#ifndef STRING_WORKER_H
#define STRING_WORKER_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *string_concatate(const char *string1,const char *string2);
int string_equal(const char *string1, const char *string2);
int string_is_empty(const char *string);
char **string_split(const char *line, const char *separators, int max_split);
char *string_lstrip(const char *string);
char *string_rstrip(const char *string);
char *string_lrstrip(const char *string);
int string_array_length(const char **string_array);
void string_free_splited_array(char **string_array);
char **string_copy_array(const char **array);
int string_find(const char *string, const char *aim);
char *string_slice(const char *string, int start, int end);
char *string_reverse(const char *string);
int string_startswith(const char *string, const char *aim);
int string_endswith(const char *string, const char *aim);
int string_is_decimal(const char *string);
int string_count(const char *string, const char *aim);
char *string_copy(const char *string);

#endif