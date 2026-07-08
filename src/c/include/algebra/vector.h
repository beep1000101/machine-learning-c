#ifndef MACHINE_LEARNING_C_VECTOR_H
#define MACHINE_LEARNING_C_VECTOR_H

#include <stddef.h>

typedef struct {
    size_t size;
    double *data;
} Vector;

void print_vector(const Vector *vector);
Vector vector_create(size_t size);
Vector vector_from_array(const double *data, size_t size);
void free_vector(Vector *vector);
Vector scalar_mul(const Vector *vector, int scalar);
Vector add_vector(const Vector *vector_left, const Vector *vector_right);
Vector sub_vector(const Vector *vector_left, const Vector *vector_right);
double dot(const Vector *vector_left, const Vector *vector_right);

#endif
