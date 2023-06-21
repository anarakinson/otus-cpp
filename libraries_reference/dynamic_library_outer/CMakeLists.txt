cmake_minimum_required(VERSION 3.12)

project(DynamicLib) 

# -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE -DBUILD_SHARED_LIBS=TRUE 
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
set ( BUILD_SHARED_LIBS TRUE )

set (
    CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/app
)
message(">>> CMAKE_SOURCE_DIR: " ${CMAKE_BINARY_DIR})

add_executable(main source/main.cpp) 

set_target_properties(  
    main PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    main 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/dynamic_lib
)

target_link_libraries(
    main 
    ${CMAKE_SOURCE_DIR}/dynamic_lib/dynamic_lib.lib
)

# add_library(dynamic_lib dynamic_lib/dynamic_lib.dll)
# set_target_properties(dynamic_lib PROPERTIES LINKER_LANGUAGE CXX)

add_custom_target(
    copy_dll
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/dynamic_lib/dynamic_lib.dll ${CMAKE_BINARY_DIR}/app/dynamic_lib.dll
)
add_dependencies(main copy_dll)