# builds helloworld binary from single source file

cmake_minimum_required(VERSION 3.12)

project(example)

set(SOURCES
    ./source/main.cpp 
    ./source/version.cpp
)

set(HEADERS 
    ./source/version.h
)

option(BUILD_EXAMPLES "qwerty 123" ON)

message("Hello! This is message. BUILD_EXAMPLES = ${BUILD_EXAMPLES}")
message("SOURCES = ${SOURCES}")

# add_executable(hello_test main.cpp version.cpp version.h)

add_executable(hello_test ${SOURCES} ${HEADERS})

set_target_properties(
    hello_test PROPERTIES 
    CXX_STANDARD 11 
    CXX_STANDARD_REQURED ON
)