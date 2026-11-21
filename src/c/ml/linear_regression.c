#include "ml/linear_regression.h"

Vector ols_regression_raw_dogged(const Matrix *design_matrix, const Vector *target_vector) {
    if (design_matrix->n_rows != target_vector->size) {
        return (Vector){0};
    }

    Matrix transpose_design_matrix = transpose(design_matrix);
    Matrix gram_matrix = multiply_matrix_matrix(&transpose_design_matrix, design_matrix);
    Vector cross_product_vector = multiply_matrix_vector(&transpose_design_matrix, target_vector);
    Vector ols_coefficients_vector = solve_gauss_elimination(&gram_matrix, &cross_product_vector);

    matrix_destroy(&transpose_design_matrix);
    matrix_destroy(&gram_matrix);
    free_vector(&cross_product_vector);

    return ols_coefficients_vector;
}