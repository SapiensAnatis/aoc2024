#include "../lib/aoc.h"
#include "day16.h"
#include "gtest/gtest.h"

TEST(day16_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day16::parse_input(input_stream);

    auto result = day16::part1(input);

    std::cout << result << std::endl;
}

TEST(day16_part1, example2) {
    auto input_stream = aoc::get_example_ifstream(2);
    auto input = day16::parse_input(input_stream);

    auto result = day16::part1(input);

    std::cout << result << std::endl;
}

TEST(day16_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day16::parse_input(input_stream);

    auto result = day16::part1(input);

    std::cout << result << std::endl;
}

TEST(day16_part2, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day16::parse_input(input_stream);

    auto result = day16::part2(input);

    std::cout << result << std::endl;
}

TEST(day16_part2, real) {}
