cmake_minimum_required(VERSION 3.5)

project(06.container)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/app 
)

add_subdirectory(source)
add_subdirectory(tests)


##################################################
# option1 - TESTS - "Make tests" ON/OFF
# option2 - LOAD_GTESTS - "Load gtests by FetchContent or use loaded directory" ON/OFF 
##################################################
