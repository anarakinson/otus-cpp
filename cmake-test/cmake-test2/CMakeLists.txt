# build two targets - lib library and main_app
# uses the add_subderictory command


cmake_minimum_required(VERSION 3.12)

project(Example2 VERSION 0.0.2)

add_subdirectory(lib)
add_subdirectory(source)