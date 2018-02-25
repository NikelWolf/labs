#include <stdio.h>
#include <stdlib.h>

#include "Complex.h"

int main() {
    Complex a, b, c;
    char a_s, b_s, op;
    printf("Enter 2 complex numbers and operation in following format: \"'first number(x +/- iy)' 'operation(+/-/*/\\) 'second number(x +/- iy)'\"\nexample: (-2 + i3) + (5 - i4)\n");

    if (scanf("(%lg %c i%lg) %c (%lg %c i%lg)", &a.re, &a_s, &a.im, &op, &b.re, &b_s, &b.im) != 7) {
        fprintf(stderr, "error in expression\nexit\n");
        exit(EXIT_FAILURE);
    } else if ((a_s != '+' || a_s != '-') && (b_s != '+' || b_s != '-')) {
        fprintf(stderr, "error in sign in expression\nexit\n");
        exit(EXIT_FAILURE);
    }

    a.im = a_s == '-' ? -a.im : a.im;
    b.im = b_s == '-' ? -b.im : b.im;

    switch (op) {
        case '+': {
            c = complex_add(a, b);
        }
        break;
        case '-': {
            c = complex_substract(a, b);
        }
        break;
        case '*': {
            c = complex_multiply(a, b);
        }
        break;
        case '\\': {
            c = complex_division(a, b);
        }
        break;
        default: {
            fprintf(stderr, "error in operation type\nunsupported operation '%c'\nexit\n", op);
            exit(EXIT_FAILURE);
        }
        break;
    }

    printf("(%lg %c i%lg) %c (%lg %c i%lg) = (%lg %c i%lg)\n", a.re, a_s, a.im < 0 ? -a.im : a.im, op, b.re, b_s, b.im < 0 ? -b.im : b.im, c.re, c.im < 0 ? '-' : '+', c.im < 0 ? -c.im : c.im);
    return 0;
}
