#include "../lib/aoc.h"
#include "day6.h"
#include "gtest/gtest.h"

TEST(day_6_part_1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day6::parse_input(input_stream);

    int result = day6::part1(input);

    std::cout << result << "\n";
}

TEST(day_6_part_1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day6::parse_input(input_stream);

    int result = day6::part1(input);

    std::cout << result << "\n";
}