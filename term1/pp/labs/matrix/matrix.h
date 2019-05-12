#ifndef MATRIX_H
#define MATRIX_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "string_worker.h"

typedef struct matrix_s {
    int rows_count;
    int column_count;
    double **array;
} matrix;

matrix *create_matrix(int rows, int columns);
void free_matrix(matrix *m);
void matrix_print(matrix *m, FILE *output);
double *matrix_copy_row(matrix *m, int row_number);
void matrix_reverse_row(matrix *m, int row_number);
double matrix_find_minimum(matrix *m, int *row_index, int *column_index);
matrix *parse_matrix(const char *string);
matrix *create_matrix_without_row_and_column(matrix *m, int row, int column);
matrix *multiply_matrix(matrix *m1, matrix *m2);

#endif
