#ifndef MACHINE_LEARNING_C_VECTOR_H
#define MACHINE_LEARNING_C_VECTOR_H

#include <stddef.h>

/**
 * @brief Heap-backed vector of double-precision values.
 */
typedef struct {
    /** Number of valid elements in @ref data. */
    size_t size;
    /** Heap buffer of @ref size elements, or NULL for an empty/invalid vector. */
    double *data;
} Vector;

/**
 * @brief Print each vector element on its own line.
 *
 * @param vector Input vector. If NULL or vector->data is NULL, nothing is printed.
 */
void print_vector(const Vector *vector);

/**
 * @brief Allocate a new vector with @p size elements.
 *
 * @param size Number of elements to allocate.
 * @return A vector with allocated storage, or an empty vector on allocation failure.
 */
Vector vector_create(size_t size);

/**
 * @brief Create a vector by copying values from a C array.
 *
 * @param data Source array.
 * @param size Number of elements to copy.
 * @return A vector containing copied values, or an empty vector if input/allocation is invalid.
 */
Vector vector_from_array(const double *data, size_t size);

/**
 * @brief Release vector storage and reset fields.
 *
 * @param vector Vector to free. Safe to call with NULL.
 */
void free_vector(Vector *vector);

/**
 * @brief Multiply a vector by an integer scalar.
 *
 * @param vector Input vector.
 * @param scalar Scalar multiplier.
 * @return New vector with scaled values, or an empty vector on invalid input/allocation failure.
 */
Vector scalar_mul(const Vector *vector, int scalar);

/**
 * @brief Add two vectors element-wise.
 *
 * @param vector_left Left input vector.
 * @param vector_right Right input vector.
 * @return New vector containing the sum, or an empty vector if inputs are invalid.
 */
Vector add_vector(const Vector *vector_left, const Vector *vector_right);

/**
 * @brief Subtract two vectors element-wise.
 *
 * @param vector_left Left input vector.
 * @param vector_right Right input vector.
 * @return New vector containing the difference, or an empty vector if inputs are invalid.
 */
Vector sub_vector(const Vector *vector_left, const Vector *vector_right);

/**
 * @brief Compute the dot product of two vectors.
 *
 * @param vector_left Left input vector.
 * @param vector_right Right input vector.
 * @return Dot product value, or 0.0 if inputs are invalid.
 */
double dot(const Vector *vector_left, const Vector *vector_right);

/**
 * @brief Compute the Euclidean norm (L2) of a vector.
 *
 * @param vector Input vector.
 * @return Euclidean norm.
 */
double norm(const Vector *vector);

/**
 * @brief Compute cosine similarity between two vectors.
 *
 * @param vector_left Left input vector.
 * @param vector_right Right input vector.
 * @return Cosine similarity in [-1, 1] for valid non-zero vectors.
 */
double cosine_similarity(const Vector *vector_left, const Vector *vector_right);

#endif
