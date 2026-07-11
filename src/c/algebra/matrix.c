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

const double *get_matrix_element_const(const Matrix *matrix, size_t row, size_t column) {
    return matrix->data + row * matrix->n_columns + column;
}

void print_matrix(const Matrix *matrix) {
    for (size_t i = 0; i < matrix->n_rows; i++) {
        for (size_t j = 0; j < matrix->n_columns; j++) {
            const double *matrix_element = get_matrix_element_const(matrix, i, j);
            printf("%f ", *matrix_element);
        }
        printf("\n");
    }
}

Matrix create_matrix(size_t n_rows, size_t n_columns) {
    Matrix matrix = {.n_rows = n_rows, .n_columns = n_columns};
    matrix.data = malloc(matrix.n_rows * matrix.n_columns * sizeof(double));
    if (matrix.data == NULL) {
        matrix.n_rows = 0;
        matrix.n_columns = 0;
    }
    return matrix;
}

Matrix matrix_from_array(const double *flat_data, size_t n_rows, size_t n_columns) {
    Matrix matrix = create_matrix(n_rows, n_columns);
    if (matrix.data == NULL || flat_data == NULL) {
        return matrix;
    }

    for (size_t i = 0; i < matrix.n_rows; i++) {
        for (size_t j = 0; j < matrix.n_columns; j++) {
            matrix.data[i * matrix.n_columns + j] = flat_data[i * matrix.n_columns + j];
        }
    }
    return matrix;
}

Matrix transpose(const Matrix *matrix) {
    Matrix transposed_matrix = create_matrix(matrix->n_columns, matrix->n_rows);
    if (transposed_matrix.data == NULL || matrix == NULL || matrix->data == NULL) {
        return transposed_matrix;
    }

    for (size_t i = 0; i < transposed_matrix.n_rows; i++) {
        for (size_t j = 0; j < transposed_matrix.n_columns; j++) {
            transposed_matrix.data[j * transposed_matrix.n_rows + i] =
                matrix->data[i * matrix->n_columns + j];
        }
    }
    return transposed_matrix;
}

double determinant_two_by_two(const Matrix *matrix) {
    if (matrix == NULL || matrix->data == NULL || matrix->n_rows != 2 || matrix->n_columns != 2) {
        return 0.0;
    }

    double determinant =
        (*get_matrix_element_const(matrix, 0, 0)) * (*get_matrix_element_const(matrix, 1, 1)) -
        (*get_matrix_element_const(matrix, 1, 0)) * (*get_matrix_element_const(matrix, 0, 1));
    return determinant;
}

int main(void) {
    size_t n_rows = 3;
    size_t n_columns = 3;
    double data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const double *flat_data = &data[0][0];
    double two_by_two[2][2] = {{1, 2}, {4, 5}};
    const double *flat_two_by_two = &two_by_two[0][0];

    Matrix matrix = matrix_from_array(flat_data, n_rows, n_columns);
    Matrix two_by_two_matrix = matrix_from_array(flat_two_by_two, 2, 2);
    Matrix transposed_matrix = transpose(&matrix);
    double two_by_two_determinant = determinant_two_by_two(&two_by_two_matrix);

    printf("Matrix:\n");
    print_matrix(&matrix);
    printf("Transposed Matrix:\n");
    print_matrix(&transposed_matrix);
    printf("2x2 Matrix:\n");
    print_matrix(&two_by_two_matrix);
    printf("2x2 Matrix determinant:\n");
    printf("%f\n", two_by_two_determinant);

    free(matrix.data);
    free(two_by_two_matrix.data);
    free(transposed_matrix.data);

    return 0;
}