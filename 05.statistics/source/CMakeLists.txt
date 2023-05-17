cmake_minimum_required(VERSION 3.5)

project(05.statistics)

add_executable(statistics
    statistics.cpp 
    statistics/meansigma.cpp
    statistics/percentile.cpp
)

set_target_properties(
    statistics PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED ON
)

include_directories(
    statistics
    PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
)
