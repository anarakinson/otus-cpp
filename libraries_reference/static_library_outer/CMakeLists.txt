cmake_minimum_required(VERSION 3.12)

project(StaticLib) 

add_executable(main source/main.cpp) 

set_target_properties(  
    main PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    main 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/static_lib
)

target_link_libraries(
    main 
    ${CMAKE_SOURCE_DIR}/static_lib/static_lib.lib
)