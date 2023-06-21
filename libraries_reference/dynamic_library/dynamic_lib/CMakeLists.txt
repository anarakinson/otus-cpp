cmake_minimum_required(VERSION 3.12)

project(DynamicLib)

set (
    CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON
)
set (
    BUILD_SHARED_LIBS TRUE
)

add_library(dynamic_lib SHARED dynamic_lib.cpp) 

set_target_properties(
    dynamic_lib PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED on
)

target_include_directories(
    dynamic_lib 
    PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
)
