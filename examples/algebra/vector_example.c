#include <stdio.h>

#include "algebra/vector.h"

int main(void) {
    int scalar = 3;
    size_t size = 3;
    double input1[] = {1.0, 3.0, 7.0};
    double input2[] = {-1.0, 2.0, 0.0};

    Vector vector1 = vector_from_array(input1, size);
    Vector vector2 = vector_from_array(input2, size);

    Vector sum_of_vectors = add_vector(&vector1, &vector2);
    Vector scalar_multiplied_vector = scalar_mul(&vector1, scalar);
    double dot_product = dot(&vector1, &vector2);
    double vector1_norm = norm(&vector1);
    double vector2_norm = norm(&vector2);
    double vector12_cosine = cosine_similarity(&vector1, &vector2);

    printf("sum of vectors:\n");
    print_vector(&sum_of_vectors);
    printf("vector1 times %d:\n", scalar);
    print_vector(&scalar_multiplied_vector);
    printf("vector1 dot vector2\n");
    printf("%f\n", dot_product);
    printf("Norm of vector1:\n");
    printf("%f\n", vector1_norm);
    printf("Norm of vector2:\n");
    printf("%f\n", vector2_norm);
    printf("Cosine similarity vector1 and vector2:\n");
    printf("%f\n", vector12_cosine);

    free_vector(&vector1);
    free_vector(&vector2);
    free_vector(&sum_of_vectors);
    free_vector(&scalar_multiplied_vector);
    return 0;
}
