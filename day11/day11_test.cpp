#include "../lib/aoc.h"
#include "day11.h"
#include "gtest/gtest.h"

TEST(day_11_part_1, example) {
    auto input_stream = aoc::get_example_ifstream();

    auto input = day11::parse_input(input_stream);

    int result = day11::part1(input);

    std::cout << result << "\n";
}

TEST(day_11_part_1, real) {}

TEST(day_11_part_2, example) {}

TEST(day_11_part_2, real) {}
