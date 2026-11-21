cmake_minimum_required(VERSION 3.20)
project(machine_learning_c LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra)

add_library(algebra_core
    src/c/algebra/vector.c
    src/c/algebra/matrix.c
)

target_include_directories(algebra_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/c/include
)
target_link_libraries(algebra_core PUBLIC m)

add_library(io_core
    src/c/io/numeric_matrix.c
)
target_link_libraries(io_core PUBLIC algebra_core)

add_library(linear_regression_core
    src/c/ml/linear_regression.c
)
target_link_libraries(linear_regression_core PUBLIC algebra_core)

add_subdirectory(examples)

enable_testing()
