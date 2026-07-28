#include "algebra/matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
    if (flat_data == NULL || n_rows == 0 || n_columns == 0) {
        return (Matrix){0};
    }

    Matrix matrix = create_matrix(n_rows, n_columns);
    if (matrix.data == NULL) {
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
    if (matrix == NULL || vector == NULL || matrix->data == NULL || vector->data == NULL ||
        matrix->n_columns != vector->size) {
        return vector_create(0);
    }
    Vector result = vector_create(matrix->n_rows);
    if (result.data == NULL) {
        return result;
    }

    for (size_t i = 0; i < matrix->n_rows; i++) {
        result.data[i] = 0.0;
        for (size_t j = 0; j < matrix->n_columns; j++) {
            result.data[i] += matrix->data[i * matrix->n_columns + j] * vector->data[j];
        }
    }

    return result;
}

Vector solve_gauss_elimination(const Matrix *matrix, const Vector *vector) {
    if (matrix == NULL || vector == NULL || matrix->data == NULL || vector->data == NULL ||
        matrix->n_rows != vector->size || matrix->n_rows != matrix->n_columns) {
        return vector_create(0);
    }

    // Start with x-buffer initialized as a copy of b; it is updated by row operations.
    Vector result = vector_create(matrix->n_rows);
    if (result.data == NULL) {
        return result;
    }
    for (size_t row = 0; row < vector->size; row++) {
        result.data[row] = vector->data[row];
    }

    // Work on a copy of A so the caller's matrix is not modified.
    Matrix dummy_matrix = matrix_from_array(matrix->data, matrix->n_rows, matrix->n_columns);
    if (dummy_matrix.data == NULL) {
        free_vector(&result);
        return vector_create(0);
    }

    const double eps = 1e-12;
    // Forward elimination: turn A into an upper-triangular matrix.
    for (size_t column = 0; column < matrix->n_columns; column++) {
        // Pick the row with largest absolute pivot in this column (partial pivoting).
        size_t target_row = column;
        double max_abs_pivot = fabs(dummy_matrix.data[column * matrix->n_columns + column]);

        for (size_t row = column + 1; row < matrix->n_rows; row++) {
            double candidate = fabs(dummy_matrix.data[row * matrix->n_columns + column]);
            if (candidate > max_abs_pivot) {
                max_abs_pivot = candidate;
                target_row = row;
            }
        }

        if (max_abs_pivot < eps) {
            // Column is effectively zero: singular or ill-conditioned system.
            matrix_destroy(&dummy_matrix);
            free_vector(&result);
            return vector_create(0);
        }

        if (target_row != column) {
            // Swap rows in both A and b so equations stay aligned.
            for (size_t inner_column = 0; inner_column < matrix->n_columns; inner_column++) {
                double tmp = dummy_matrix.data[column * matrix->n_columns + inner_column];
                dummy_matrix.data[column * matrix->n_columns + inner_column] =
                    dummy_matrix.data[target_row * matrix->n_columns + inner_column];
                dummy_matrix.data[target_row * matrix->n_columns + inner_column] = tmp;
            }

            double tmp_result = result.data[column];
            result.data[column] = result.data[target_row];
            result.data[target_row] = tmp_result;
        }

        // Eliminate entries below the pivot in this column.
        for (size_t row = column + 1; row < matrix->n_rows; row++) {
            double multiplier = dummy_matrix.data[row * matrix->n_columns + column] /
                                dummy_matrix.data[column * matrix->n_columns + column];
            result.data[row] = result.data[row] - multiplier * result.data[column];
            for (size_t inner_column = column; inner_column < matrix->n_columns; inner_column++) {
                dummy_matrix.data[row * matrix->n_columns + inner_column] =
                    dummy_matrix.data[row * matrix->n_columns + inner_column] +
                    (-multiplier) * dummy_matrix.data[column * matrix->n_columns + inner_column];
            }
        }
    }

    // Back-substitution: solve Ux = y from bottom row to top row.
    for (size_t i = matrix->n_rows; i-- > 0;) {
        double sum = result.data[i];
        for (size_t j = i + 1; j < matrix->n_columns; j++) {
            sum -= dummy_matrix.data[i * matrix->n_columns + j] * result.data[j];
        }

        double pivot = dummy_matrix.data[i * matrix->n_columns + i];
        if (fabs(pivot) < eps) {
            matrix_destroy(&dummy_matrix);
            free_vector(&result);
            return vector_create(0);
        }

        result.data[i] = sum / pivot;
    }

    matrix_destroy(&dummy_matrix);
    return result;
}
