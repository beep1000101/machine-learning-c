#include <stdio.h>
#include <stdlib.h>

typedef struct{
    size_t size;
    double* data;
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

Vector add_vector(Vector vector_left, Vector vector_right) {
    Vector result = vector_create(vector_left.size);
    for (int i = 0; i < vector_left.size; i++){
        result.data[i] = vector_left.data[i] + vector_right.data[i];
    }

    return result;
}

int main(){
    size_t size = 3;
    double input1[] = {1.0, 3.0, 7.0};
    Vector vector1 = vector_from_array(input1, size);
    double input2[] = {-1.0, 2.0, 0.0};
    Vector vector2 = vector_from_array(input2, size);

    Vector sum_of_vectors = add_vector(vector1, vector2);

    printf("sum of vectors:\n");
    print_vector(sum_of_vectors);


    free_vector(vector1);
    free_vector(vector2);
    return 0;
}