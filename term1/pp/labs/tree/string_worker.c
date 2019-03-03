#define _GNU_SOURCE

#include "string_worker.h"

char *string_concatate(const char *string1, const char *string2) {
    char *msg;
    asprintf(&msg, "%s%s", string1, string2);
    return msg;
}

int string_equal(const char *string1, const char *string2) {
    return !strcmp(string1, string2) ? 1 : 0;
}

int string_is_empty(const char *string) {
    return string_equal(string, "");
}

char **string_split(const char *line, const char *separators, int max_split) {
    int array_size = 0;
    char *token = NULL, *str = NULL, *tofree = NULL;
    char **array = (char **) calloc(array_size+1, sizeof(char **));
    array_size++;

    tofree = str = strdup(line);
    if(max_split != 0) {
        while(max_split && (token = strsep(&str, separators))) {
            if(!string_equal(token, "")) {
                char **tmp_array = (char **) calloc(array_size+1, sizeof(char **));
                int i;
                for(i = 0; i < array_size-1; i++) {
                    tmp_array[i] = array[i];
                }
                tmp_array[array_size-1] = strdup(token);

                free(array);
                array = tmp_array;

                array_size++;
                max_split--;
            }
        }
    } else {
        free(array);
        array = (char **) calloc(2, sizeof(char **));
        array[0] = strdup(str);
    }
    free(tofree);

    return array;
}

char *string_lstrip(const char *string) {
    int not_whitespace_index = 0;
    size_t i;
    for(i = 0; i < strlen(string); i++) {
        if(isspace(string[i]))
            not_whitespace_index++;
        else
            break;
    }
    char *new_string = strdup(string+not_whitespace_index);
    return new_string;
}

char *string_rstrip(const char *string) {
    int not_whitespace_index = strlen(string);
    int i;
    for(i = strlen(string)-1; i >= 0; i--) {
        if(isspace(string[i]))
            not_whitespace_index--;
        else
            break;
    }
    char *str_tmp = strdup(string);
    str_tmp[not_whitespace_index] = '\0';
    char *new_string = strdup(str_tmp);
    free(str_tmp);
    return new_string;
}

char *string_lrstrip(const char *string) {
    char *lstriped_string = string_lstrip(string);
    char *rstriped_string = string_rstrip(lstriped_string);
    free(lstriped_string);
    return rstriped_string;
}

int string_array_length(const char **string_array) {
    if(!string_array)
        return 0;

    int length = 0;
    while(*string_array++) {
        length++;
    }
    return length;
}

void string_free_splited_array(char **string_array) {
    int i;
    for(i = 0; string_array[i]; i++) {
        free(string_array[i]);
    }

    free(string_array);
}

char **string_copy_array(const char **array) {
    int array_length = string_array_length((const char **) array) + 1;

    char **copy_array = (char **) calloc(array_length, sizeof(char *));

    int i;
    for(i = 0; i < array_length-1; i++) {
        copy_array[i] = string_copy(array[i]);
    }

    return copy_array;
}

int string_find(const char *string, const char *aim) {
    char *tmp;
    if(!(tmp = strstr(string, aim)))
        return -1;
    else
        return (int) (tmp - string);
}

char *string_slice(const char *string, int start, int end) {
    if((size_t) start >= strlen(string) || start < 0 || (end <= start && end >= 0))
        return strdup("");

    if((size_t) end > strlen(string))
        end = strlen(string);

    if(end < 0) {
        end = end % strlen(string);

        end = strlen(string) - end;
    }

    char *new_string = (char *) calloc(end-start, sizeof(char));
    strncpy(new_string, string+start, end-start);

    return new_string;
}

char *string_reverse(const char *string) {
    char *new_string = strdup("");
    int i;
    for(i = strlen(string)-1; i >= 0; i--)
        asprintf(&new_string, "%s%c", new_string, string[i]);

    return new_string;
}

int string_startswith(const char *string, const char *aim) {
    if(string_find(string, aim) == 0)
        return 1;

    return 0;
}

int string_endswith(const char *string, const char *aim) {
    if(strlen(string) < strlen(aim))
        return 0;

    char *rev_string = string_reverse(string);
    char *rev_aim = string_reverse(aim);
    int result = 0;
    if(string_find(rev_string, rev_aim) != -1 && string_find(rev_string, rev_aim) == 0)
        result = 1;
    else
        result = 0;

    free(rev_string);
    free(rev_aim);

    return result;
}

int string_is_decimal(const char *string) {
    while(*string)
        if(!isdigit(*string++))
            return 0;

    return 1;
}

int string_count(const char *string, const char *aim) {
    int offset = 0;
    int count = 0;
    while(string_find(string+offset, aim) != -1) {
        offset += string_find(string+offset, aim)+1;
        count++;
    }

    return count;
}

char *string_copy(const char *string) {
    char *new_string = (char *) calloc((strlen(string) + 1), sizeof(char));

    strcpy(new_string, string);

    return new_string;
}
