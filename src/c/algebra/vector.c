#include "algebra/vector.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void print_vector(const Vector *vector) {
    if (vector == NULL || vector->data == NULL) {
        return;
    }

    for (size_t i = 0; i < vector->size; i++) {
        printf("%f\n", vector->data[i]);
    }
}

Vector vector_create(size_t size) {
    Vector vector = {.size = size, .data = NULL};

    if (size == 0) {
        return vector;
    }

    vector.data = malloc(size * sizeof(double));
    if (vector.data == NULL) {
        vector.size = 0;
    }

    return vector;
}

Vector vector_from_array(const double *data, size_t size) {
    Vector vector = vector_create(size);
    if (vector.data == NULL || data == NULL) {
        return vector;
    }

    for (size_t i = 0; i < vector.size; i++) {
        vector.data[i] = data[i];
    }
    return vector;
}

void free_vector(Vector *vector) {
    if (vector == NULL) {
        return;
    }

    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
}

Vector scalar_mul(const Vector *vector, int scalar) {
    if (vector == NULL || vector->data == NULL) {
        return vector_create(0);
    }

    Vector result = vector_create(vector->size);
    if (result.data == NULL) {
        return result;
    }

    for (size_t i = 0; i < vector->size; i++) {
        result.data[i] = vector->data[i] * scalar;
    }
    return result;
}

Vector add_vector(const Vector *vector_left, const Vector *vector_right) {
    if (vector_left == NULL || vector_right == NULL || vector_left->data == NULL ||
        vector_right->data == NULL || vector_left->size != vector_right->size) {
        return vector_create(0);
    }

    Vector result = vector_create(vector_left->size);
    if (result.data == NULL) {
        return result;
    }

    for (size_t i = 0; i < vector_left->size; i++) {
        result.data[i] = vector_left->data[i] + vector_right->data[i];
    }

    return result;
}

Vector sub_vector(const Vector *vector_left, const Vector *vector_right) {
    if (vector_left == NULL || vector_right == NULL || vector_left->data == NULL ||
        vector_right->data == NULL || vector_left->size != vector_right->size) {
        return vector_create(0);
    }

    Vector result = vector_create(vector_left->size);
    if (result.data == NULL) {
        return result;
    }

    for (size_t i = 0; i < vector_left->size; i++) {
        result.data[i] = vector_left->data[i] - vector_right->data[i];
    }

    return result;
}

double dot(const Vector *vector_left, const Vector *vector_right) {
    if (vector_left == NULL || vector_right == NULL || vector_left->data == NULL ||
        vector_right->data == NULL || vector_left->size != vector_right->size) {
        return 0.0;
    }

    double result = 0.0;
    for (size_t i = 0; i < vector_left->size; i++) {
        result += vector_left->data[i] * vector_right->data[i];
    }
    return result;
}

double norm(const Vector *vector) {
    double sum_of_squares = 0;
    for (size_t i = 0; i < vector->size; i++) {
        sum_of_squares += vector->data[i] * vector->data[i];
    }
    double norm = sqrt(sum_of_squares);
    return norm;
}

double cosine_similarity(const Vector *vector_left, const Vector *vector_right) {
    double dot_product = dot(vector_left, vector_right);
    double norm_left = norm(vector_left);
    double norm_right = norm(vector_right);
    double cosine_similarity = dot_product / (norm_left * norm_right);
    return cosine_similarity;
}