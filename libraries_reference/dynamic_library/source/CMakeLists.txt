cmake_minimum_required(VERSION 3.12)

project(DynamicLib) 

add_executable(main main.cpp) 

set_target_properties(  
    main PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    main 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(
    main 
    dynamic_lib
)