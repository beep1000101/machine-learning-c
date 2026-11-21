#include "io/numeric_matrix.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int read_numeric_features_and_target(const char *path, size_t feature_count, Matrix *features,
                                     Vector *target) {
    if (path == NULL || features == NULL || target == NULL || feature_count == 0 ||
        feature_count == SIZE_MAX) {
        return 0;
    }
    *features = (Matrix){0};
    *target = (Vector){0};

    size_t field_count = feature_count + 1;

    FILE *input = fopen(path, "r");
    if (input == NULL) {
        return 0;
    }

    double *values = NULL;
    size_t value_count = 0;
    size_t capacity = 0;
    int valid = 1;

    while (1) {
        double value;
        int result = fscanf(input, "%lf", &value);
        if (result == EOF) {
            break;
        }
        if (result != 1) {
            valid = 0;
            break;
        }

        if (value_count == capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            if (new_capacity < capacity || new_capacity > SIZE_MAX / sizeof(*values)) {
                valid = 0;
                break;
            }
            double *grown_values = realloc(values, new_capacity * sizeof(*values));
            if (grown_values == NULL) {
                valid = 0;
                break;
            }
            values = grown_values;
            capacity = new_capacity;
        }
        values[value_count++] = value;
    }

    if (ferror(input)) {
        valid = 0;
    }
    fclose(input);

    if (!valid || value_count == 0 || value_count % field_count != 0) {
        free(values);
        return 0;
    }

    size_t row_count = value_count / field_count;
    Matrix loaded_features = create_matrix(row_count, feature_count);
    Vector loaded_target = vector_create(row_count);
    if (loaded_features.data == NULL || loaded_target.data == NULL) {
        matrix_destroy(&loaded_features);
        free_vector(&loaded_target);
        free(values);
        return 0;
    }

    for (size_t row = 0; row < row_count; row++) {
        for (size_t feature = 0; feature < feature_count; feature++) {
            loaded_features.data[row * feature_count + feature] =
                values[row * field_count + feature];
        }
        loaded_target.data[row] = values[row * field_count + feature_count];
    }

    free(values);
    *features = loaded_features;
    *target = loaded_target;
    return 1;
}