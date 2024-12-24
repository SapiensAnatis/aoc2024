#include "../lib/aoc.h"
#include "day15.h"
#include "gtest/gtest.h"

TEST(day15_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day15::parse_input(input_stream);

    auto result = day15::part1(input);

    std::cout << result << std::endl;
}

TEST(day15_part1, example2) {
    auto input_stream = aoc::get_example_ifstream(2);
    auto input = day15::parse_input(input_stream);

    auto result = day15::part1(input);

    std::cout << result << std::endl;
}

TEST(day15_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day15::parse_input(input_stream);

    auto result = day15::part1(input);

    std::cout << result << std::endl;
}

TEST(day15_part2, example) {}

TEST(day15_part2, real) {}
