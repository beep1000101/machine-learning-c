#include <stdio.h>

#define Dimension 3

struct Vector {
    float elements[Dimension];
};

struct Matrix {
    float elements[Dimension][Dimension];
};

void multiply_matrix_vector(const struct Matrix *matrix, const struct Vector *vector,
                            struct Vector *result) {
    for (int row = 0; row < Dimension; row++) {
        result->elements[row] = 0.0f;
        for (int column = 0; column < Dimension; column++) {
            result->elements[row] += matrix->elements[row][column] * vector->elements[column];
        }
    }
}

float dot_product(const struct Vector *left, const struct Vector *right) {
    float result = 0.0f;
    for (int i = 0; i < Dimension; i++) {
        result += left->elements[i] * right->elements[i];
    }
    return result;
}

int main(void) {
    struct Matrix matrix = {.elements = {{1, 0, 0}, {-1, 1, 1}, {-1, 0, 1}}};

    struct Vector vector = {.elements = {1, 3, 1}};
    struct Vector vector2 = {.elements = {-1, 2, 2}};
    struct Vector result;

    multiply_matrix_vector(&matrix, &vector, &result);
    printf("[%f, %f, %f]\n", result.elements[0], result.elements[1], result.elements[2]);

    float dot = dot_product(&vector, &vector2);
    printf("%f\n", dot);

    return 0;
}