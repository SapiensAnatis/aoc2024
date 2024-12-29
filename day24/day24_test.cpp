#include "../lib/aoc.h"
#include "day24.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <format>

TEST(day24_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day24);
    auto input = day24::parse_input(input_stream);

    auto result = day24::part1(input);

    ASSERT_EQ(result, 4);
}

TEST(day24_part1, example2) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day24, 2);
    auto input = day24::parse_input(input_stream);

    auto result = day24::part1(input);

    ASSERT_EQ(result, 2024);
}

TEST(day24_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day24);
    auto input = day24::parse_input(input_stream);

    auto result = day24::part1(input);

    std::cout << result << std::endl;
}

TEST(day24_part2, example) {}

TEST(day24_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day24);
    auto input = day24::parse_input(input_stream);

    day24::part2(input);

    // did this by hand
    std::vector<std::string> involved_in_swaps = {"z12", "qdg", "z19", "vvf",
                                                  "fgn", "dck", "z37", "nvh"};

    std::sort(involved_in_swaps.begin(), involved_in_swaps.end());
    auto join = aoc::join(',', involved_in_swaps.begin(), involved_in_swaps.end());

    std::cout << join << std::endl;
}
