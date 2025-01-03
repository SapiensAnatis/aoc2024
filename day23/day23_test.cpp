#include "../lib/aoc.h"
#include "day23.h"

#include "gtest/gtest.h"
#include <algorithm>
#include <ranges>

TEST(day23_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day23);
    auto input = day23::parse_input(input_stream);

    auto result = day23::part1(input);

    ASSERT_EQ(result, 7);
}

TEST(day23_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day23);
    auto input = day23::parse_input(input_stream);

    auto result = day23::part1(input);

    std::cout << result << std::endl;
}

TEST(day23_part2, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day23);
    auto input = day23::parse_input(input_stream);

    auto result = day23::part2(input);

    ASSERT_EQ(result, "co,de,ka,ta");
}

TEST(day23_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day23);
    auto input = day23::parse_input(input_stream);

    auto result = day23::part2(input);

    std::cout << result << std::endl;
}
