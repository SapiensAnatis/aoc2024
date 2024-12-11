#include "../lib/aoc.h"
#include "day8.h"
#include "gtest/gtest.h"

TEST(day_8_part_1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day8::parse_input(input_stream);

    int result = day8::part1(input);

    std::cout << result << std::endl;
}
