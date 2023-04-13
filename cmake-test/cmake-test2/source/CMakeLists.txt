cmake_minimum_required(VERSION 3.12)

project(Main VERSION 0.0.5)

configure_file(
    config.h.in 
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

add_executable(main_app main.cpp)

set_target_properties(
    main_app PROPERTIES 
    CXX_STANDARD 14 
    CXX_STANDARD_REQURED ON
)
target_include_directories(
    main_app
    PRIVATE 
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_include_directories(
    main_app
    PRIVATE 
    ${CMAKE_CURRENT_BINARY_DIR}/../lib
)
target_link_libraries(main_app lib)