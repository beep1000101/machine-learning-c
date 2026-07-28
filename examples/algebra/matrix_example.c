#include <stdio.h>

#include "algebra/matrix.h"

int main(void) {
    size_t n_rows = 3;
    size_t n_columns = 3;
    double two_by_two[2][2] = {{3, 2}, {4, 5}};
    const double *flat_two_by_two = &two_by_two[0][0];
    double data[3][3] = {{2, 1, 3}, {0, 1, 4}, {5, 2, 0}};
    double big_data[4][4] = {{3, 1, 2, 4}, {0, 1, 5, 2}, {2, 0, 3, 1}, {1, 4, 2, 6}};
    double rectangular_data[2][3] = {{1, 2, 3}, {4, 5, 6}};
    const double *flat_data = &data[0][0];
    const double *flat_big_data = &big_data[0][0];

    Matrix matrix = matrix_from_array(flat_data, n_rows, n_columns);
    Matrix matrix_inverted = invert_matrix_naive(&matrix);
    Matrix big_matrix = matrix_from_array(flat_big_data, 4, 4);
    Matrix big_matrix_inverted = invert_matrix_naive(&big_matrix);
    Matrix two_by_two_matrix = matrix_from_array(flat_two_by_two, 2, 2);
    Matrix two_by_two_matrix_iverted = invert_matrix_naive(&two_by_two_matrix);
    Matrix transposed_matrix = transpose(&matrix);
    Matrix rectangular = matrix_from_array(&rectangular_data[0][0], 2, 3);
    Matrix rectangular_transposed = transpose(&rectangular);

    double two_by_two_determinant = determinant_two_by_two(&two_by_two_matrix);
    double determinant = matrix_determinant(&matrix);
    double determinant_big_matrix = matrix_determinant(&big_matrix);

    printf("Matrix:\n");
    print_matrix(&matrix);
    printf("Inverted Matrix:\n");
    print_matrix(&matrix_inverted);
    printf("Transposed Matrix:\n");
    print_matrix(&transposed_matrix);
    printf("Rectangular matrix:\n");
    print_matrix(&rectangular);
    printf("Rectangular transpose:\n");
    print_matrix(&rectangular_transposed);
    printf("2x2 Matrix:\n");
    print_matrix(&two_by_two_matrix);
    printf("Inverted 2x2 Matrix:\n");
    print_matrix(&two_by_two_matrix_iverted);
    printf("2x2 Matrix determinant:\n");
    printf("%f\n", two_by_two_determinant);
    printf("Matrix determinant:\n");
    printf("%f\n", determinant);
    printf("Big Matrix:\n");
    print_matrix(&big_matrix);
    printf("Big Inverted Matrix:\n");
    print_matrix(&big_matrix_inverted);
    printf("Big Matrix determinant:\n");
    printf("%f\n", determinant_big_matrix);

    matrix_destroy(&matrix);
    matrix_destroy(&two_by_two_matrix);
    matrix_destroy(&transposed_matrix);
    matrix_destroy(&big_matrix);
    matrix_destroy(&rectangular);
    matrix_destroy(&rectangular_transposed);
    matrix_destroy(&matrix_inverted);
    matrix_destroy(&two_by_two_matrix_iverted);
    matrix_destroy(&big_matrix_inverted);

    // next round 3x3 matrix
    double elimination_data[3][3] = {{1, 1, 1}, {1, 3, 1}, {4, -1, 1}};
    const double *elimination_data_flat = &elimination_data[0][0];
    double elimiation_vector_data[3] = {5, 9, -2};
    Matrix matrix_elimination = matrix_from_array(elimination_data_flat, 3, 3);
    Vector vector_elimination = vector_from_array(elimiation_vector_data, 3);

    Vector elimination_result_vector =
        solve_gauss_elimination(&matrix_elimination, &vector_elimination);
    printf("Gauss example 1 (expected solution: -1, 2, 4):\n");
    print_vector(&elimination_result_vector);
    matrix_destroy(&matrix_elimination);
    free_vector(&vector_elimination);
    free_vector(&elimination_result_vector);

    // pivoting-heavy system with known solution x = [2, -1, 3]
    double elimination_data_pivot[3][3] = {{0, 2, 1}, {1, -2, -3}, {3, -1, 2}};
    const double *elimination_data_pivot_flat = &elimination_data_pivot[0][0];
    double elimination_vector_data_pivot[3] = {1, -5, 13};
    Matrix matrix_elimination_pivot = matrix_from_array(elimination_data_pivot_flat, 3, 3);
    Vector vector_elimination_pivot = vector_from_array(elimination_vector_data_pivot, 3);

    Vector elimination_result_vector_pivot =
        solve_gauss_elimination(&matrix_elimination_pivot, &vector_elimination_pivot);
    printf("Gauss example 2 (pivoting, expected solution: 2, -1, 3):\n");
    print_vector(&elimination_result_vector_pivot);
    matrix_destroy(&matrix_elimination_pivot);
    free_vector(&vector_elimination_pivot);
    free_vector(&elimination_result_vector_pivot);

    return 0;
}
