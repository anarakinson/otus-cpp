cmake_minimum_required(VERSION 3.5)

project(vcpkg)
 

if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

enable_testing()

find_package(GTest CONFIG REQUIRED)

add_executable(
    tests
    tests.cpp
)

# Add src to the include directories for the test target
target_include_directories(
    tests PRIVATE
    "${CMAKE_SOURCE_DIR}/source"
)

# Link test target against gtest libraries
target_link_libraries(
    tests PRIVATE
    GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
)
add_test(AllTestsInMain main)
