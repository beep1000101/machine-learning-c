#include <stdio.h>
#include <stdlib.h>

typedef struct{
    size_t size;
    double* data;
} Vector;

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

int main(){
    size_t size = 3;
    double input[] = {1.0, 3.0, 7.0};
    Vector vector = vector_from_array(input, size);

    for (size_t i = 0; i < vector.size; i++) {
        printf("%f\n", vector.data[i]);
    }


    free(vector.data);
    return 0;
}