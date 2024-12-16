#include "../lib/aoc.h"
#include "day12.h"
#include "gtest/gtest.h"

TEST(day12_part1, example) {
    auto input_stream = aoc::get_example_ifstream();

    auto input = day12::parse_input(input_stream);

    int result = day12::part1(input);

    std::cout << result << "\n";
}

TEST(day12_part1, example2) {
    auto input_stream = aoc::get_example_ifstream(2);

    auto input = day12::parse_input(input_stream);

    int result = day12::part1(input);

    std::cout << result << "\n";
}

TEST(day12_part1, example3) {
    auto input_stream = aoc::get_example_ifstream(3);

    auto input = day12::parse_input(input_stream);

    int result = day12::part1(input);

    std::cout << result << "\n";
}

TEST(day12_part1, real) {
    auto input_stream = aoc::get_real_ifstream();

    auto input = day12::parse_input(input_stream);

    int result = day12::part1(input);

    std::cout << result << "\n";
}

TEST(day12_part2, example) {}

TEST(day12_part2, real) {}
