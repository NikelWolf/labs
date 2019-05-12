#include <stdlib.h>
#include <time.h>

#include "matrix.h"

matrix *create_random_matrix(int rows_count, int columns_count) {
    srand(time(NULL));

    matrix *m = create_matrix(rows_count, columns_count);

    int i;
    for (i = 0; i < m->rows_count; i++) {
        int j;
        for (j = 0; j < m->column_count; j++) {
            m->array[i][j] = (double)(rand() % 1000);
        }
    }

    return m;
}

int main() {
    int random_matrix_row_count;
    int random_matrix_column_count;
    char *line = NULL;
    size_t s = 0;
    printf("enter rows count and columns count in matrix that will be filled with random numbers: ");
    getline(&line, &s, stdin);
    sscanf(line, "%d %d", &random_matrix_row_count, &random_matrix_column_count);
    if (random_matrix_row_count <= 2 || random_matrix_column_count <= 3) {
        printf("wrong numbers\nexit\n");
        exit(EXIT_FAILURE);
    }

    matrix *m = create_random_matrix(random_matrix_row_count, random_matrix_column_count);

    printf("generated matrix:\n");
    matrix_print(m, stdout);
    printf("\n\n");

    matrix_reverse_row(m, 0);
    matrix_reverse_row(m, m->rows_count - 1);

    printf("generated matrix with reversed rows(%d, %d):\n", 0, m->rows_count - 1);
    matrix_print(m, stdout);
    printf("\n\n");

    int min_row, min_column;
    double number;
    number = matrix_find_minimum(m, &min_row, &min_column);
    printf("minimum(%10.5lf) was found on %d row and %d column\nmatrix with deleted row and columns that contain minimum number:\n", number, min_row, min_column);
    matrix *t = create_matrix_without_row_and_column(m, min_row, min_column);
    matrix_print(t, stdout);
    printf("\n\n");

    line = NULL;
    s = 0;
    printf("enter line to parse: ");
    getline(&line, &s, stdin);

    matrix *m2 = parse_matrix(line);

    if (m2) {
        printf("parsed matrix:\n");
        matrix_print(m2, stdout);
        printf("\n\n");
    } else {
        printf("input is not right\nexit\n");
        exit(EXIT_FAILURE);
    }

    matrix *mat = multiply_matrix(t, m2);
    if (mat) {
        printf("multiply matrix:\n");
        matrix_print(t, stdout);
        printf("\non matrix:\n");
        matrix_print(m2, stdout);
        printf("\n");
        printf("equal matrix:\n");
        matrix_print(mat, stdout);
        printf("\n\n");
    } else {
        printf("error while multyply matrix\n");
    }

    return 0;
}
