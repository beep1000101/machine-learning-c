#include <stdio.h>

#define Dimension 3

struct Vector {
    float elements[Dimension];
};

struct Matrix {
    float elements[Dimension][Dimension];
};

void multiply_matrix_vector(const float matrix[Dimension][Dimension], const float vector[Dimension], float result[Dimension]){
    for(int row=0; row < Dimension; row++){
        result[row] = 0.0f;
        for(int column=0; column < Dimension; column++){
            result[row] = result[row] + matrix[row][column] * vector[column];
        }
    }
}

int main(void){
    float matrix[Dimension][Dimension] = {
        {1,0,0},
        {-1,1,1},
        {-1,0,1}
    };
    float vector[Dimension] = {1,3,1};
    float result[Dimension];

    multiply_matrix_vector(matrix, vector, result);
    printf("[%f, %f, %f]\n", result[0], result[1], result[2]);

    return 0;
}
