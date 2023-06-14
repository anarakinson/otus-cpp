cmake_minimum_required(VERSION 3.5)

project(06.container)

#################################
option(TESTS "Make tests" ON)
option(LOAD_GTESTS "Load gtests by FetchContent or use loaded directory" ON) 

#################################
# tests
#################################
if (TESTS)
    message(">>> Make tests")
    if (MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    ################################
    # loaded googletest
    ################################
    if (LOAD_GTESTS)
        message("\n>>> Load gtest")
        include(FetchContent)

        # build from sources at build time
        FetchContent_Declare(
            googletest 
            GIT_REPOSITORY https://github.com/google/googletest.git 
            GIT_TAG main
            # GIT_TAG 703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
        )
        FetchContent_MakeAvailable(googletest)

    ################################
    # included googletest directiry
    ################################
    else()
        message("\n>>> Use loaded gtest")
        add_subdirectory(
            "${CMAKE_SOURCE_DIR}/googletest" 
            "googletest"
        )
    endif()

    ################################

    # Test target
    add_executable(
        tests
        tests.cpp
        general_tests.cpp
        array_tests.cpp
        vector_tests.cpp
        list_tests.cpp
    )

    # Add src to the include directories for the test target
    target_include_directories(
        tests PRIVATE
        "${CMAKE_SOURCE_DIR}/source"
        "${CMAKE_SOURCE_DIR}/source/mycontainer"
        "${CMAKE_SOURCE_DIR}/source/myarray"
        "${CMAKE_SOURCE_DIR}/source/myvector"
        "${CMAKE_SOURCE_DIR}/source/mylist"
    )

    # Link test target against gtest libraries
    target_link_libraries(
        tests PRIVATE
        gtest gtest_main
    )

    set_target_properties(tests 
        PROPERTIES CXX_STANDARD 17 
        CXX_STANDARD_REQUIRED ON 
    )

    # set compile options
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
endif()