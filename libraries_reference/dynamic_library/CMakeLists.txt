cmake_minimum_required(VERSION 3.12)

project(Project_lib)

set (
    CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/app
)

add_subdirectory(dynamic_lib)
add_subdirectory(source)