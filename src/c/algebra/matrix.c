#include "algebra/vector.h"
#include <math.h>
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

void matrix_destroy(Matrix *matrix) {
    if (matrix == NULL) {
        return;
    }

    free(matrix->data);
    matrix->data = NULL;
    matrix->n_rows = 0;
    matrix->n_columns = 0;
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
    if (matrix == NULL || matrix->data == NULL) {
        return (Matrix){0};
    }

    Matrix transposed_matrix = create_matrix(matrix->n_columns, matrix->n_rows);
    if (transposed_matrix.data == NULL) {
        return transposed_matrix;
    }

    for (size_t i = 0; i < matrix->n_rows; i++) {
        for (size_t j = 0; j < matrix->n_columns; j++) {
            transposed_matrix.data[j * transposed_matrix.n_columns + i] =
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

static Matrix build_minor(const Matrix *matrix, size_t skip_row, size_t skip_col) {
    Matrix minor = create_matrix(matrix->n_rows - 1, matrix->n_columns - 1);
    if (minor.data == NULL) {
        return minor;
    }

    size_t delta_row = 0;
    for (size_t r = 0; r < matrix->n_rows; r++) {
        if (r == skip_row) {
            continue;
        }
        size_t delta_column = 0;
        for (size_t c = 0; c < matrix->n_columns; c++) {
            if (c == skip_col) {
                continue;
            }
            minor.data[delta_row * minor.n_columns + delta_column] =
                matrix->data[r * matrix->n_columns + c];
            delta_column++;
        }
        delta_row++;
    }

    return minor;
}

double matrix_determinant(const Matrix *matrix) {
    if (matrix == NULL || matrix->data == NULL) {
        return 0.0;
    }
    if (matrix->n_rows != matrix->n_columns || matrix->n_rows == 0) {
        return 0.0;
    }
    if (matrix->n_rows == 1) {
        return matrix->data[0];
    }
    if (matrix->n_rows == 2) {
        return determinant_two_by_two(matrix);
    }

    double determinant = 0.0;
    for (size_t col = 0; col < matrix->n_columns; col++) {
        Matrix minor = build_minor(matrix, 0, col);
        if (minor.data == NULL) {
            return 0.0;
        }

        double sign = (col % 2 == 0) ? 1.0 : -1.0;
        double a0c = *get_matrix_element_const(matrix, 0, col);
        determinant += sign * a0c * matrix_determinant(&minor);

        matrix_destroy(&minor);
    }

    return determinant;
}

Matrix invert_matrix_naive(const Matrix *matrix) {
    if (matrix == NULL || matrix->data == NULL || matrix->n_rows != matrix->n_columns ||
        matrix->n_rows == 0) {
        return (Matrix){0};
    }

    double determinant = matrix_determinant(matrix);
    if (fabs(determinant) < 1e-12) {
        return (Matrix){0};
    }

    Matrix inverted_matrix = create_matrix(matrix->n_rows, matrix->n_columns);
    if (inverted_matrix.data == NULL) {
        return inverted_matrix;
    }

    if (matrix->n_rows == 1) {
        inverted_matrix.data[0] = 1.0 / matrix->data[0];
        return inverted_matrix;
    }

    for (size_t i = 0; i < inverted_matrix.n_rows; i++) {
        for (size_t j = 0; j < inverted_matrix.n_columns; j++) {
            Matrix minor = build_minor(matrix, i, j);
            if (minor.data == NULL) {
                matrix_destroy(&inverted_matrix);
                return (Matrix){0};
            }
            double minor_determinant = matrix_determinant(&minor);
            matrix_destroy(&minor);
            double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            inverted_matrix.data[j * inverted_matrix.n_columns + i] =
                sign * minor_determinant / determinant;
        }
    }

    return inverted_matrix;
}

Vector multiply_matrix_vector(const Matrix *matrix, const Vector *vector) {
    double *result = malloc(matrix->n_columns * sizeof(double));
    for (int i = 0; i < matrix->n_rows; i++) {
        result[i] = 0.0f;
        for (int j = 0; j < matrix->n_columns; j++) {
            result[i] += matrix->data[i * matrix->n_columns + j] * vector->data[j];
        }
    }
    Vector result_vector = vector_from_array(result, matrix->n_columns);
    return result_vector
}

int main(void) {
    size_t n_rows = 3;
    size_t n_columns = 3;
    double two_by_two[2][2] = {{3, 2}, {4, 5}};
    const double *flat_two_by_two = &two_by_two[0][0];
    double data[3][3] = {{2, 1, 3}, {0, 1, 4}, {5, 2, 0}};
    double big_data[4][4] = {{3, 1, 2, 4}, {0, 1, 5, 2}, {2, 0, 3, 1}, {1, 4, 2, 6}};
    double rectangular_data[2][3] = {{1, 2, 3}, {4, 5, 6}};
    const double *flat_data = &data[0][0];
    const double *flat_big_data = &big_data[0][0];

    Matrix matrix = matrix_from_array(flat_data, n_rows, n_columns);
    Matrix matrix_inverted = invert_matrix_naive(&matrix);
    Matrix big_matrix = matrix_from_array(flat_big_data, 4, 4);
    Matrix big_matrix_inverted = invert_matrix_naive(&big_matrix);
    Matrix two_by_two_matrix = matrix_from_array(flat_two_by_two, 2, 2);
    Matrix two_by_two_matrix_iverted = invert_matrix_naive(&two_by_two_matrix);
    Matrix transposed_matrix = transpose(&matrix);
    Matrix rectangular = matrix_from_array(&rectangular_data[0][0], 2, 3);
    Matrix rectangular_transposed = transpose(&rectangular);

    double two_by_two_determinant = determinant_two_by_two(&two_by_two_matrix);
    double determinant = matrix_determinant(&matrix);
    double determinant_big_matrix = matrix_determinant(&big_matrix);

    printf("Matrix:\n");
    print_matrix(&matrix);
    printf("Inverted Matrix:\n");
    print_matrix(&matrix_inverted);
    printf("Transposed Matrix:\n");
    print_matrix(&transposed_matrix);
    printf("Rectangular matrix:\n");
    print_matrix(&rectangular);
    printf("Rectangular transpose:\n");
    print_matrix(&rectangular_transposed);
    printf("2x2 Matrix:\n");
    print_matrix(&two_by_two_matrix);
    printf("Inverted 2x2 Matrix:\n");
    print_matrix(&two_by_two_matrix_iverted);
    printf("2x2 Matrix determinant:\n");
    printf("%f\n", two_by_two_determinant);
    printf("Matrix determinant:\n");
    printf("%f\n", determinant);
    printf("Big Matrix:\n");
    print_matrix(&big_matrix);
    printf("Big Inverted Matrix:\n");
    print_matrix(&big_matrix_inverted);
    printf("Big Matrix determinant:\n");
    printf("%f\n", determinant_big_matrix);

    matrix_destroy(&matrix);
    matrix_destroy(&two_by_two_matrix);
    matrix_destroy(&transposed_matrix);
    matrix_destroy(&big_matrix);
    matrix_destroy(&rectangular);
    matrix_destroy(&rectangular_transposed);
    matrix_destroy(&matrix_inverted);
    matrix_destroy(&two_by_two_matrix_iverted);
    matrix_destroy(&big_matrix_inverted);

    return 0;
}