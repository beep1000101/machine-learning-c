#include "algebra/matrix.h"
#include "algebra/vector.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// X.T @ X @ b = X.T @ y
// b = (X.T @ X)**-1 @ X.T @ y

Vector linear_regression_raw_dogged(const Matrix *sample_matrix, const Vector *target_vector) {
    Vector dumb_vector = {.size = 0, .data = NULL};
    return dumb_vector;
}