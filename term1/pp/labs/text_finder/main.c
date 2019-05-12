#define _GNU_SOURCE

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatate_strings(int argc, char *args[]) {
    char *full_string = strdup("");
    asprintf(&full_string, "%s%s", full_string, args[0]);
    int i;
    for (i = 1; i < argc; i++) {
        asprintf(&full_string, "%s %s", full_string, args[i]);
    }
    return full_string;
}

int suffix_match(const char *aim, size_t aim_len, size_t offset, size_t suffix_len) {
    if (offset > suffix_len)
        return aim[offset - suffix_len - 1] != aim[aim_len - suffix_len - 1] &&
               strncmp(aim + aim_len - suffix_len, aim + offset - suffix_len, suffix_len) == 0;
    else
        return strncmp(aim + aim_len - offset, aim, offset) == 0;
}

size_t max(size_t a, size_t b) {
    return a > b ? a : b;
}

const char *boyer_moore_string_finder(const char *string, const char *aim) {
    size_t string_len = strlen(string);
    size_t aim_len = strlen(aim);

    size_t *suffix_table = (size_t *)malloc(sizeof(size_t) * aim_len);
    size_t *stop_table = (size_t *)malloc(sizeof(size_t) * (UCHAR_MAX + 1));

    if (aim_len > string_len || aim_len <= 0 || !string || !aim)
        return NULL;

    size_t index;
    for (index = 0; index < UCHAR_MAX + 1; index++)
        stop_table[index] = -1;

    for (index = 0; index < aim_len - 1; index++)
        stop_table[(size_t)aim[index]] = index;

    for (index = 0; index < aim_len; index++) {
        size_t offset = aim_len;
        while (offset && !suffix_match(aim, aim_len, offset, index))
            --offset;
        suffix_table[aim_len - index - 1] = aim_len - offset;
    }

    size_t string_position;
    for (string_position = 0; string_position <= string_len - aim_len;) {

        size_t aim_position = aim_len - 1;
        while (aim[aim_position] == string[aim_position + string_position]) {
            if (aim_position == 0)
                return string + string_position;

            --aim_position;
        }

        string_position += max(suffix_table[aim_position], aim_position - stop_table[(size_t)string[aim_position + string_position]]);
    }

    return NULL;
}

int string_find(const char *string, const char *aim, const char *(*find_algorithm)(const char *, const char *)) {
    const char *tmp = find_algorithm(string, aim);

    return tmp ? (int)(tmp - string) : -1;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "usage: line_finder filename [-s] line_word1 [line_word2]...\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "file is not accessible\n");
        exit(EXIT_FAILURE);
    }

    int words_start = 2;
    int verbose = 1;

    if (strcmp(argv[words_start], "-s") == 0 && argc >= 4) {
        words_start++;

        verbose = 0;
    }

    char *full_string = concatate_strings(argc - words_start, argv + words_start);

    printf("aim: %s\n\n", full_string);

    int was_found = 0;
    int line_number = 1;
    while (!feof(file)) {
        char *line = NULL;
        size_t size = 0;
        getline(&line, &size, file);

        int offset = 0;

        while (string_find(line + offset, full_string, boyer_moore_string_finder) != -1) {
            offset += string_find(line + offset, full_string, boyer_moore_string_finder) + 1;

            was_found = 1;

            if (verbose) {
                printf("line %d, position %d: %s\n", line_number, offset, line + offset - 1);
            }
        }

        line_number++;

        free(line);
    }

    if (!was_found) {
        printf("NOT FOUND\n");
    }

    free(full_string);

    return 0;
}
