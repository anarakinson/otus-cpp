cmake_minimum_required(VERSION 3.5)

project(python_module)


#######################################
# pybind11
find_package(pybind11 CONFIG REQUIRED)
pybind11_add_module(
    pyfibonacci
    module.cpp 
    fibonacci.cpp
)
list(APPEND TARGETS pyfibonacci)

# add correct extention to python module
if (WIN32)
    # set_target_properties(pyfibonacci PROPERTIES OUTPUT_NAME pyfibonacci.pyd)       # rename
    add_custom_command(
        TARGET pyfibonacci POST_BUILD                                                 # copy and rename
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/cpp/Debug/pyfibonacci ${CMAKE_BINARY_DIR}/cpp/Debug/pyfibonacci.pyd
    )
endif()


#######################################
# make library
add_library(
    fibonacci SHARED
    fibonacci.cpp 
)
target_include_directories(
    fibonacci
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
list(APPEND TARGETS fibonacci)


#######################################
# make tests
add_executable(
    fibonacci_test
    fibonacci_tests.cpp 
)
list(APPEND TARGETS fibonacci_test)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(
    fibonacci_test 
    fibonacci 
    GTest::gtest_main
)
include(GoogleTest)

gtest_discover_tests(fibonacci_test)

add_test(fibonacci fibonacci_test)


#######################################
# set properties
foreach(target ${TARGETS}) 
    
    set_target_properties(
        ${target} PROPERTIES 
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON 
    )

    if(
        CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
    )
        target_compile_options(
            ${target}
            PRIVATE 
            -g -Wall -Wextra -Werror -pedantic
        )
            
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(
            ${target}
            PRIVATE
            /W4 /WX
        )
    endif()

endforeach()
