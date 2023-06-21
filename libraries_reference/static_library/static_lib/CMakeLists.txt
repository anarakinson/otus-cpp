cmake_minimum_required(VERSION 3.12)

project(StaticLib)

add_library(static_lib STATIC static_lib.cpp) 

set_target_properties(
    static_lib PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED on
)

target_include_directories(
    static_lib 
    PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)