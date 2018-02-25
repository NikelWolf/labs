#include <stdio.h>
#include <stdlib.h>

#include "Complex.h"

int main() {
    FILE *file = fopen("complex.txt", "r");
    if (!file) {
        fprintf(stderr, "error while opening file\nexit\n");
        exit(EXIT_FAILURE);
    }

    int n;
    if (fscanf(file, "%d\n", &n) != 1) {
        fprintf(stderr, "error while reading number\nexit\n");
        exit(EXIT_FAILURE);
    }

    Complex *numbers = (Complex *) malloc(sizeof(Complex)*n);
    int i;
    char n_s;
    int max = 0;
    for (i = 0; i < n; i++) {
        if (fscanf(file, "(%lg %c i%lg)\n", &numbers[i].re, &n_s, &numbers[i].im) != 3) {
            fprintf(stderr, "error while reading complex number on line %d\nexit\n", i);
            exit(EXIT_FAILURE);
        }
        numbers[i].im = n_s == '-' ? -numbers[i].im : numbers[i].im;

        if (complex_abs(numbers[i]) > complex_abs(numbers[max])) {
            max = i;
        }
    }

    printf("max complex number in file is (%lg %c i%lg)\n", numbers[max].re, numbers[max].im < 0 ? '-' : '+', numbers[max].im < 0 ? -numbers[max].im : numbers[max].im);
    return 1;
}
