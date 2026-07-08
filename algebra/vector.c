#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    double *data;
} Vector;

void print_vector(Vector vector) {
    for (size_t i = 0; i < vector.size; i++) {
        printf("%f\n", vector.data[i]);
    }
}

Vector vector_create(size_t size) {
    Vector vector;
    vector.size = size;
    vector.data = malloc(vector.size * sizeof(double));

    return vector;
}

Vector vector_from_array(const double *data, size_t size) {
    Vector vector = vector_create(size);
    for (size_t i = 0; i < vector.size; i++) {
        vector.data[i] = data[i];
    }
    return vector;
}

void free_vector(Vector vector) {
    free(vector.data);
}

Vector scalar_mul(Vector vector, int scalar) {
    Vector result = vector_create(vector.size);
    for (size_t i = 0; i < vector.size; i++) {
        result.data[i] = vector.data[i] * scalar;
    }
    return result;
}

Vector add_vector(Vector *vector_left, Vector *vector_right) {
    Vector result = vector_create(vector_left->size);
    for (size_t i = 0; i < vector_left->size; i++) {
        result.data[i] = vector_left->data[i] + vector_right->data[i];
    }

    return result;
}

Vector sub_vector(Vector vector_left, Vector vector_right) {
    Vector result = vector_create(vector_left.size);
    for (size_t i = 0; i < vector_left.size; i++) {
        result.data[i] = vector_left.data[i] - vector_right.data[i];
    }

    return result;
}

double dot(Vector vector_left, Vector vector_right) {
    double result = 0;
    for (size_t i = 0; i < vector_left.size; i++) {
        result += vector_left.data[i] * vector_right.data[i];
    }
    return result;
}

int main() {
    int scalar = 3;
    size_t size = 3;
    double input1[] = {1.0, 3.0, 7.0};
    Vector vector1 = vector_from_array(input1, size);
    double input2[] = {-1.0, 2.0, 0.0};
    Vector vector2 = vector_from_array(input2, size);

    Vector sum_of_vectors = add_vector(&vector1, &vector2);
    Vector scalar_multiplied_vector = scalar_mul(vector1, scalar);
    double dot_product = dot(vector1, vector2);

    printf("sum of vectors:\n");
    print_vector(sum_of_vectors);
    printf("vector1 times %d:\n", scalar);
    print_vector(scalar_multiplied_vector);
    printf("vector1 dot vector2\n");
    printf("%f\n", dot_product);

    free_vector(vector1);
    free_vector(vector2);
    free_vector(sum_of_vectors);
    free_vector(scalar_multiplied_vector);
    return 0;
}
