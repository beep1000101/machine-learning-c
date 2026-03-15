#include <stdio.h>

void multiply_matrix_vector(const float matrix[3][3], const float vector[3], float result[3]){
    for(int row=0; row < 3; row++){
        result[row] = 0.0f;
        for(int column=0; column < 3; column++){
            result[row] = result[row] + matrix[row][column] * vector[column];
        }
    }
}

int main(void){
    float matrix[3][3] = {
        {1,0,0},
        {0,1,0},
        {0,0,1}
    };
    float vector[3] = {1,1,1};
    float result[3];

    multiply_matrix_vector(matrix, vector, result);
    printf("[%f, %f, %f]\n", result[0], result[1], result[2]);

    return 0;
}