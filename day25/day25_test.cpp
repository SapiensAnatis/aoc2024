#include "../lib/aoc.h"
#include "day25.h"
#include "gtest/gtest.h"

TEST(day25_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day25);
    auto input = day25::parse_input(input_stream);

    auto result = day25::part1(input);

    ASSERT_EQ(result, 3);
}

TEST(day25_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day25);
    auto input = day25::parse_input(input_stream);

    auto result = day25::part1(input);

    std::cout << result << std::endl;
}

TEST(day25_part2, example) {}

TEST(day25_part2, real) {}
