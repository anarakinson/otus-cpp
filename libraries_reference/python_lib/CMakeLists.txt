cmake_minimum_required(VERSION 3.5)

project(python_module)


enable_language(C)
enable_language(CXX)


# set compile properties
set (
    CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON
)
set (
    BUILD_SHARED_LIBS TRUE
)
set(
    CMAKE_CXX_CLANG_TIDY clang-tidy -warnings-as-errors=*
)


# set vcpkg properties
if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(
        CMAKE_TOOLCHAIN_FILE
        "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING ""
    )
endif()


enable_testing()

add_subdirectory(cpp)
