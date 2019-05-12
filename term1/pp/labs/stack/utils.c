#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

double get_number(const char *string, unsigned int *offset) {
    char *tmp;
    double number = strtod(string + *offset, &tmp);
    *offset += (tmp - (string + *offset));

    return number;
}

int is_operator(char c) {
    if (c == '-' || c == '+' || c == '*' || c == '/' || c == '\\' || c == '=') {
        return 1;
    }

    return 0;
}

operator_type get_operator(const char *string, unsigned int *offset) {
    switch (string[*offset]) {
    case '-': {
        *offset += 1;
        return MINUS;
    }
    case '+': {
        *offset += 1;
        return PLUS;
    }
    case '*': {
        *offset += 1;
        return MULTIPLE;
    }
    case '/': {
        *offset += 1;
        return DIVIDE;
    }
    case '\\': {
        *offset += 1;
        return DIVIDE;
    }
    case '=': {
        *offset += 1;
        return EQUAL;
    }
    default: {
        *offset += 1;
        return UNKNOWN;
    }
    }
}

object_type get_object(const char *string, unsigned int *offset, double *operand_element, int *operator_element) {
    if (string && offset) {
        if (*offset < strlen(string)) {
            if (isdigit(string[*offset])) {
                *operand_element = get_number(string, offset);
                return NUMBER;
            } else if (is_operator(string[*offset])) {
                *operator_element = get_operator(string, offset);
                return OPERATOR;
            } else if (isspace(string[*offset])) {
                *offset += 1;
                return get_object(string, offset, operand_element, operator_element);
            } else {
                *offset += 1;
                return ERROR;
            }
        } else {
            return END;
        }
    } else {
        return ERROR;
    }
}
