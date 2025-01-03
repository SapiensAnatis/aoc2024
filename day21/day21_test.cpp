#include "../lib/aoc.h"
#include "day21.h"
#include "gtest/gtest.h"

TEST(day21_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day21);
    auto input = day21::parse_input(input_stream);

    auto result = day21::part1(input);

    std::cout << result << std::endl;
}

TEST(day21_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day21);
    auto input = day21::parse_input(input_stream);

    auto result = day21::part1(input);

    std::cout << result << std::endl;
}

TEST(day21_part2, example) {}

TEST(day21_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day21);
    auto input = day21::parse_input(input_stream);

    auto result = day21::part2(input);

    std::cout << result << std::endl;
}
