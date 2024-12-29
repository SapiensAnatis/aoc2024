#include "../lib/aoc.h"
#include "day24.h"
#include "gtest/gtest.h"

TEST(day24_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day24::parse_input(input_stream);

    auto result = day24::part1(input);

    ASSERT_EQ(result, 4);
}

TEST(day24_part1, example2) {
    auto input_stream = aoc::get_example_ifstream(2);
    auto input = day24::parse_input(input_stream);

    auto result = day24::part1(input);

    ASSERT_EQ(result, 2024);
}

TEST(day24_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day24::parse_input(input_stream);

    auto result = day24::part1(input);

    // this is probably wrong because of how I prioritize operations
    // don't iterate the list in order
    std::cout << result << std::endl;
}

TEST(day24_part2, example) {}

TEST(day24_part2, real) {}
