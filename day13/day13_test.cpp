#include "../lib/aoc.h"
#include "day13.h"
#include "gtest/gtest.h"

TEST(day13_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    const auto input = day13::parse_input(input_stream);

    auto result = day13::part1(input);

    std::cout << result << std::endl;
}

TEST(day13_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    const auto input = day13::parse_input(input_stream);

    auto result = day13::part1(input);

    std::cout << result << std::endl;
}

TEST(day13_part2, example) {
    auto input_stream = aoc::get_example_ifstream();
    const auto input = day13::parse_input(input_stream);

    auto result = day13::part2(input);

    std::cout << result << std::endl;
}

TEST(day13_part2, real) {
    auto input_stream = aoc::get_real_ifstream();
    const auto input = day13::parse_input(input_stream);

    auto result = day13::part2(input);

    std::cout << result << std::endl;
}
