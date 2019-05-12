#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "utils.h"

int main() {
    char *string = NULL;
    size_t s = 0;
    unsigned int offset = 0;
    double operand_element = 0;
    int operator_element;
    int object = 0;
    stack *st = create_stack(sizeof(double));
    push(st, &operand_element);

    if (getline(&string, &s, stdin) != -1) {
        while ((object = get_object(string, &offset, &operand_element, &operator_element)) != END) {
            switch (object) {
            case NUMBER: {
                if (!push(st, &operand_element)) {
                    fprintf(stderr, "push error\n");
                    exit(EXIT_FAILURE);
                }
            } break;
            case OPERATOR: {
                if (operator_element != EQUAL) {
                    double op1;
                    double op2;
                    if (!pop(st, &op1)) {
                        fprintf(stderr, "pop op1 error: %lf\n", op1);
                        exit(EXIT_FAILURE);
                    }
                    if (!pop(st, &op2)) {
                        fprintf(stderr, "pop op2 error: %lf\n", op2);
                        exit(EXIT_FAILURE);
                    }
                    switch (operator_element) {
                    case PLUS: {
                        double result = op1 + op2;
                        if (!push(st, &result)) {
                            fprintf(stderr, "push error\n");
                        }
                    } break;
                    case MINUS: {
                        double result = op1 - op2;
                        if (!push(st, &result)) {
                            fprintf(stderr, "push error\n");
                        }
                    } break;
                    case DIVIDE: {
                        double result = op1 / op2;
                        if (!push(st, &result)) {
                            fprintf(stderr, "push error\n");
                        }
                    } break;
                    case MULTIPLE: {
                        double result = op1 * op2;
                        if (!push(st, &result)) {
                            fprintf(stderr, "push error\n");
                        }
                    } break;
                    }
                } else {
                    double result;
                    pop(st, &result);
                    printf("%.3lf\n", result);
                    exit(EXIT_SUCCESS);
                }
            } break;
            case ERROR: {
                fprintf(stderr, "error in string\n");
                exit(EXIT_FAILURE);
            } break;
            }
        }
        if (object == END) {
            double result;
            pop(st, &result);
            printf("\nwarning: missing equal sign '='. Result is %.3lf\n", result);
        }
    } else {
        fprintf(stderr, "error on input\n");
        exit(EXIT_FAILURE);
    }

    free_stack(st);

    return 0;
}
