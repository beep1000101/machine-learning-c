#ifndef MACHINE_LEARNING_C_LINEAR_REGRESSION_H
#define MACHINE_LEARNING_C_LINEAR_REGRESSION_H

#include "algebra/matrix.h"

Vector ols_regression_raw_dogged(const Matrix *design_matrix, const Vector *target_vector);

#endif