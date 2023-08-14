cmake_minimum_required(VERSION 3.12)

project(08.threading)


add_executable(
    topk_words 
    src/topk_words.cpp
)

include_directories(
    include
)

set_target_properties(
    topk_words PROPERTIES 
    SXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


if (MSVC)
    target_compile_options(
        topk_words PRIVATE
        /W4
    )
else ()
    target_compile_options(
        topk_words PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
