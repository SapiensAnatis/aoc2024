cmake_minimum_required(VERSION 3.30)
project(aoc2024)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/7927f8e93d2cc7788229ab446179fdfda15e75e4.zip
)

FetchContent_MakeAvailable(googletest)

# https://gitlab.kitware.com/cmake/cmake/-/issues/26283
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy;-warnings-as-errors=*")
add_compile_options(-Wall -Wextra -Wpedantic -Werror)


add_subdirectory("lib")
link_libraries(lib)

add_subdirectory("day01")
add_subdirectory("day02")
add_subdirectory("day03")
add_subdirectory("day04")
add_subdirectory("day05")
add_subdirectory("day06")
add_subdirectory("day07")
add_subdirectory("day08")
add_subdirectory("day09")
add_subdirectory("day10")
add_subdirectory("day11")
add_subdirectory("day12")
