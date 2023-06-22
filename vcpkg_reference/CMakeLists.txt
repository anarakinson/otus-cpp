cmake_minimum_required(VERSION 3.5) 

project(vcpkg) 


set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/app 
)


add_subdirectory(source)
add_subdirectory(tests)

##################################
# vcpkg integrate install
# CMAKE_TOOLCHAIN_FILE="${PATH}"
##################################

set_target_properties(
    main PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(
        tests PRIVATE
        /W4
    )
else ()
    target_compile_options(
        tests PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()