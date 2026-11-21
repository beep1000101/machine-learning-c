#ifndef MACHINE_LEARNING_C_NUMERIC_MATRIX_H
#define MACHINE_LEARNING_C_NUMERIC_MATRIX_H

#include "algebra/matrix.h"

int read_numeric_features_and_target(const char *path, size_t feature_count, Matrix *features,
                                     Vector *target);

#endif