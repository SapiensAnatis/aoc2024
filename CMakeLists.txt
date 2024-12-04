cmake_minimum_required(VERSION 3.30)
project(aoc2024)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS:FILEPATH /usr/lib/llvm-17/bin/clang-scan-deps)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/7927f8e93d2cc7788229ab446179fdfda15e75e4.zip
)

FetchContent_MakeAvailable(googletest)

add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory("day1")
add_subdirectory("day3")
add_subdirectory("day4")