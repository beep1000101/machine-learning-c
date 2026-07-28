add_executable(vector_example
    vector_example.c
)
target_link_libraries(vector_example PRIVATE algebra_core)

add_executable(dot_product_example
    dot_product_example.c
)

add_executable(matrix_example
    matrix_example.c
)
target_link_libraries(matrix_example PRIVATE algebra_core)
