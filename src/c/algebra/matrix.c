#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t n_rows;
    size_t n_columns;
    double *data;
} Matrix;

double *get_matrix_element(Matrix *matrix, size_t row, size_t column) {
    return matrix->data + row * matrix->n_columns + column;
}

void print_matrix(Matrix *matrix) {
    for (size_t i = 0; i < matrix->n_rows; i++) {
        for (size_t j = 0; j < matrix->n_columns; j++) {
            double *matrix_element = get_matrix_element(matrix, i, j);
            printf("%f ", *matrix_element);
        }
        printf("\n");
    }
}

Matrix create_matrix(size_t n_rows, size_t n_columns) {
    Matrix matrix = {.n_rows = n_rows, .n_columns = n_columns};
    matrix.data = malloc(matrix.n_rows * matrix.n_columns * sizeof(double));
    return matrix;
}

Matrix matrix_from_array(const double *flat_data, size_t n_rows, size_t n_columns) {
    Matrix matrix = create_matrix(n_rows, n_columns);
    for (size_t i = 0; i < matrix.n_rows; i++) {
        for (size_t j = 0; j < matrix.n_columns; j++) {
            matrix.data[i * matrix.n_columns + j] = flat_data[i * matrix.n_columns + j];
        }
    }
    return matrix;
}

int main(void) {
    size_t n_rows = 3;
    size_t n_columns = 3;
    double data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const double *flat_data = &data[0][0];

    Matrix matrix = matrix_from_array(flat_data, n_rows, n_columns);
    print_matrix(&matrix);

    free(matrix.data);

    return 0;
}