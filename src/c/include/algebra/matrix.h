#ifndef MACHINE_LEARNING_C_MATRIX_H
#define MACHINE_LEARNING_C_MATRIX_H

#include <stddef.h>

#include "algebra/vector.h"

typedef struct {
    size_t n_rows;
    size_t n_columns;
    double *data;
} Matrix;

double *get_matrix_element(Matrix *matrix, size_t row, size_t column);
const double *get_matrix_element_const(const Matrix *matrix, size_t row, size_t column);

void print_matrix(const Matrix *matrix);

Matrix create_matrix(size_t n_rows, size_t n_columns);
void matrix_destroy(Matrix *matrix);
Matrix matrix_from_array(const double *flat_data, size_t n_rows, size_t n_columns);

Matrix transpose(const Matrix *matrix);

double determinant_two_by_two(const Matrix *matrix);
double matrix_determinant(const Matrix *matrix);

Matrix invert_matrix_naive(const Matrix *matrix);

Vector multiply_matrix_vector(const Matrix *matrix, const Vector *vector);
Vector solve_gauss_elimination(const Matrix *matrix, const Vector *vector);

#endif
