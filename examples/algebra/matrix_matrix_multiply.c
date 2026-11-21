#include <stdio.h>

#include "algebra/matrix.h"

int main(void) {
    const double left_data[] = {1, 2, 3, 4, 5, 6};
    const double right_data[] = {7, 8, 9, 10, 11, 12, 13, 14};
    const double expected_product_data[] = {29, 32, 35, 38, 65, 72, 79, 86, 101, 112, 123, 134};

    Matrix left_matrix = matrix_from_array(left_data, 3, 2);
    Matrix right_matrix = matrix_from_array(right_data, 2, 4);
    // Reference result for checking multiply_matrix_matrix once its indexing is corrected.
    Matrix expected_product = matrix_from_array(expected_product_data, 3, 4);

    if (left_matrix.data == NULL || right_matrix.data == NULL || expected_product.data == NULL) {
        matrix_destroy(&left_matrix);
        matrix_destroy(&right_matrix);
        matrix_destroy(&expected_product);
        return 1;
    }

    printf("Left matrix (3x2):\n");
    print_matrix(&left_matrix);
    printf("Right matrix (2x4):\n");
    print_matrix(&right_matrix);
    Matrix product_result = multiply_matrix_matrix(&left_matrix, &right_matrix);

    printf("Product result (3x4):\n");
    print_matrix(&product_result);

    printf("Expected product (3x4):\n");
    print_matrix(&expected_product);

    matrix_destroy(&left_matrix);
    matrix_destroy(&right_matrix);
    matrix_destroy(&expected_product);
    matrix_destroy(&product_result);
    return 0;
}