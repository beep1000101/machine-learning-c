#include <stdio.h>
#include <stdlib.h>

#include "io/numeric_matrix.h"
#include "ml/linear_regression.h"

#ifndef REGRESSION_DATA_PATH
#define REGRESSION_DATA_PATH "../../data/regression_datapoints.txt"
#endif

#define FEATURE_COUNT 3

static void release_regression_resources(Matrix *features, Vector *targets, Vector *coefficients,
                                         Vector *predictions) {
    matrix_destroy(features);
    free_vector(targets);
    free_vector(coefficients);
    free_vector(predictions);
}

int main(int argc, char **argv) {
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [path/to/regression_datapoints.txt]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *data_path = argc == 2 ? argv[1] : REGRESSION_DATA_PATH;
    Matrix features = {0};
    Vector targets = {0};
    Vector coefficients = {0};
    Vector predictions = {0};

    if (!read_numeric_features_and_target(data_path, FEATURE_COUNT, &features, &targets)) {
        fprintf(stderr, "Could not read numeric dataset: %s\n", data_path);
        release_regression_resources(&features, &targets, &coefficients, &predictions);
        return EXIT_FAILURE;
    }

    coefficients = ols_regression_raw_dogged(&features, &targets);
    if (coefficients.data == NULL) {
        fprintf(stderr, "Could not solve OLS normal equations; check for dependent features\n");
        release_regression_resources(&features, &targets, &coefficients, &predictions);
        return EXIT_FAILURE;
    }

    predictions = multiply_matrix_vector(&features, &coefficients);
    if (predictions.data == NULL || predictions.size != targets.size) {
        fprintf(stderr, "Could not calculate predictions\n");
        release_regression_resources(&features, &targets, &coefficients, &predictions);
        return EXIT_FAILURE;
    }

    double squared_error_sum = 0.0;
    for (size_t row = 0; row < targets.size; row++) {
        double error = predictions.data[row] - targets.data[row];
        squared_error_sum += error * error;
    }

    printf("Observations: %zu\n", features.n_rows);
    printf("Features: %zu\n", features.n_columns);
    printf("OLS coefficients (one per feature):\n");
    print_vector(&coefficients);
    printf("Training MSE: %.12g\n", squared_error_sum / targets.size);

    release_regression_resources(&features, &targets, &coefficients, &predictions);
    return EXIT_SUCCESS;
}