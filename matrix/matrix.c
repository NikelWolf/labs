#include "matrix.h"

static void init_matrix(matrix *m, int rows, int column) {
    m->rows_count = rows;
    m->column_count = column;
    m->array = (double **) malloc(sizeof(double *) * rows);
    int i;
    for(i = 0; i < rows; i++)
        m->array[i] = (double *) calloc(column, sizeof(double));
}

matrix *create_matrix(int rows, int columns) {
    matrix *m = (matrix *) malloc(sizeof(matrix));

    init_matrix(m, rows, columns);

    return m;
}

void free_matrix(matrix *m) {
    if(m) {
        if(m->array) {
            int i;
            for(i = 0; i < m->rows_count; i++)
                free(m->array[i]);

            free(m->array);
        }

        free(m);
    }
}

void matrix_print(matrix *m, FILE *output) {
    int i;
    for(i = 0; i < m->rows_count; i++) {
        int j;
        for(j = 0; j < m->column_count; j++) {
            fprintf(output, "%10.3lf ", m->array[i][j]);
        }
        fprintf(output, "\n");
    }
}

double *matrix_copy_row(matrix *m, int row_number) {
    if(row_number >= m->rows_count || row_number < 0) 
        return NULL;

    double *tmp = (double *) malloc(sizeof(double) * m->column_count);
    memcpy(tmp, m->array[row_number], m->column_count * sizeof(double));

    return tmp;
}

void reverse_row(double *row, int elements_count) {
    int i;
    for(i = 0; i < elements_count/2; i++) {
        double tmp = row[i];
        row[i] = row[elements_count - i - 1];
        row[elements_count - i - 1] = tmp;
    }
}

void matrix_reverse_row(matrix *m, int row_number) {
    double *tmp;

    if((tmp = matrix_copy_row(m, row_number)) == NULL)
        return;

    reverse_row(tmp, m->column_count);

    free(m->array[row_number]);
    m->array[row_number] = tmp;
}

void matrix_switch_rows(matrix *m, int row1, int row2) {
    double *tmp = m->array[row1];
    m->array[row1] = m->array[row2];
    m->array[row2] = tmp;
}

matrix *create_matrix_without_row_and_column(matrix *m, int row, int column) {
    matrix *tmp = create_matrix(m->rows_count-1, m->column_count-1);

    int i, j, k, n;
    for (i = 0, k = 0; i < m->rows_count; i++, k++) {
        if (i == row){
            k--;
            continue;
        }
        for (j = 0, n = 0; j < m->column_count; j++, n++) {
            if(j == column) {
                n--;
                continue;
            }
            tmp->array[k][n] = m->array[i][j];
        }
    }

    return tmp;
}

double matrix_find_minimum(matrix *m, int *row_index, int *column_index) {
    int min_number = m->array[0][0];
    int min_row_index = 0;
    int min_column_index = 0;

    int i;
    for(i = 0; i < m->rows_count; i++) {
        int j;
        for(j = 0; j < m->column_count; j++) {
            if(min_number < m->array[i][j]) {
                min_number = m->array[i][j];
                
                min_row_index = i;
                min_column_index = j;
            }
        }
    }

    *row_index = min_row_index;
    *column_index = min_column_index;

    return min_number;
}

static int check_string(const char *string) {
    while(*string) {
        if(isdigit(*string) || *string == ',' || *string == '.' || isspace(*string))
            string++;
        else 
            return 0;
    }

    return 1;
}

matrix *parse_matrix(const char *string) {
    if(!check_string(string))
        return NULL;

    if(string_find(string, ".") == -1)
        return NULL;

    char *new_string = string_slice(string, 0, string_find(string, "."));

    char **rows = string_split(new_string, ",", -1);
    int rows_count = string_array_length(rows);
    char **tmp_splited_column = string_split(rows[0], " ", -1);
    int columns_count = string_array_length(tmp_splited_column);

    matrix *m = create_matrix(rows_count, columns_count);

    string_free_splited_array(tmp_splited_column);
    int i;
    for(i = 0; i < rows_count; i++) {
        char **columns = string_split(rows[i], " ", -1);
        if(columns_count != string_array_length(columns)) {
            string_free_splited_array(rows);
            string_free_splited_array(columns);
            free_matrix(m);

            printf("columns != splited\n%d %d \n", columns_count, string_array_length(columns));

            return NULL;
        }

        int j;
        for(j = 0; j < columns_count; j++) {
            m->array[i][j] = strtod(columns[j], (char **) NULL);
        }
    }

    return m;
}

matrix *multiply_matrix(matrix *m1, matrix *m2) {
    if(m1->column_count != m2->rows_count) {
        printf("columns in first matrix are not equal to rows in second matrix\n");
        return NULL;
    }

    matrix *m = create_matrix(m1->rows_count, m2->column_count);

    int i, j, t;
    for (i = 0; i < m->rows_count; ++i){
        for (j = 0; j < m->column_count; ++j){
            for (t = 0; t < m1->rows_count; ++t){
                m->array[i][j] += m1->array[i][t] * m2->array[t][j];
            }
        }
    }

    return m;
}