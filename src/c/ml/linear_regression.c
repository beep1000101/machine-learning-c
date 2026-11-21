#include "algebra/matrix.h"
#include "algebra/vector.h"

// X.T @ X @ b = X.T @ y
// b = (X.T @ X)**-1 @ X.T @ y

Vector ols_regression_raw_dogged(const Matrix *design_matrix, const Vector *target_vector) {
    Matrix transpose_design_matrix = transpose(&design_matrix);
    Matrix gram_matrix = multiply_matrix_matrix(&transpose_design_matrix, &design_matrix);
    Matrix inverse_gram_matrix = invert_matrix_naive(&gram_matrix);
    Vector cross_product_vector = multiply_matrix_vector(&transpose_design_matrix, &target_vector);

    Vector ols_coefficients_vector =
        multiply_matrix_vector(&inverse_gram_matrix, &cross_product_vector);
    return ols_coefficients_vector;
}