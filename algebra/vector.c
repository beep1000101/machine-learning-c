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

int main(){
    Vector vector = vector_create(3);
    if (vector.data == NULL) {
        return 1;
    }

    double input[] = {1.0, 3.0, 7.0};

    for (size_t i = 0; i < vector.size; i++) {
        vector.data[i] = input[i];
    }

    for (size_t i = 0; i < vector.size; i++) {
        printf("%f\n", vector.data[i]);
    }


    free(vector.data);
    return 0;
}