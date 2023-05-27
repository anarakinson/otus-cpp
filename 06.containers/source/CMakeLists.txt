cmake_minimum_required(VERSION 3.5)

project(06.container)

add_executable(container
    run_tests.cpp 
)

include_directories(
    mycontainer
    myarray
    mylist
    myvector
    utils
    PUBLIC  
    ${CMAKE_CURRENT_BINARY_DIR}
)

set_target_properties(container
    PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)