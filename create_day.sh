#!/usr/bin/bash

# And they say C# has boilerplate...

day=$1 

if [ -z "$day" ]; then
    echo "Usage: ./create_day.sh <day_number>"
    exit 1
fi

printf -v $day_name "day%02d" $day
mkdir -p $day_name

touch ./${day_name}/input.txt
touch ./${day_name}/example.txt

tee ./${day_name}/CMakeLists.txt <<EOF > /dev/null
configure_file("\${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "\${CMAKE_CURRENT_BINARY_DIR}/example.txt" COPYONLY)

if (EXISTS "\${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
    configure_file("\${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "\${CMAKE_CURRENT_BINARY_DIR}/input.txt" COPYONLY)
endif ()

add_executable(${day_name}_test ${day_name}.cpp
        ${day_name}_test.cpp
        ${day_name}.h)

target_link_libraries(${day_name}_test gtest_main)
EOF

tee ./${day_name}/${day_name}.cpp <<EOF > /dev/null
#include "${day_name}.h"

namespace ${day_name} {
} // namespace ${day_name}
EOF

include_guard="AOC2024_${day_name}_H"

tee ./${day_name}/${day_name}.h <<EOF > /dev/null
#ifndef ${include_guard}
#define ${include_guard}

namespace ${day_name} {
} // namespace ${day_name}

#endif // ${include_guard}
EOF

tee ./${day_name}/${day_name}_test.cpp <<EOF > /dev/null
#include "../lib/aoc.h"
#include "${day_name}.h"
#include "gtest/gtest.h"

TEST(${day_name}_part1, example) {
}

TEST(${day_name}_part1, real) {
}

TEST(${day_name}_part2, example) {
}

TEST(${day_name}_part2, real) {
}
EOF

if [ -z $(grep ${day_name} CMakeLists.txt) ]; then
    echo "add_subdirectory(\"${day_name}\")" >> CMakeLists.txt
fi