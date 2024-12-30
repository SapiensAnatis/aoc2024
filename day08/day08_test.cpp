#include "../lib/aoc.h"
#include "day08.h"
#include "gtest/gtest.h"

TEST(day08_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day08);
    auto input = day08::parse_input(input_stream);

    int result = day08::part1(input);

    std::cout << result << std::endl;
}

TEST(day08_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day08);
    auto input = day08::parse_input(input_stream);

    int result = day08::part1(input);

    std::cout << result << std::endl;
}

TEST(day08_part2, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day08);
    auto input = day08::parse_input(input_stream);

    int result = day08::part2(input);

    std::cout << result << std::endl;
}

TEST(day08_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day08);
    auto input = day08::parse_input(input_stream);

    int result = day08::part2(input);

    std::cout << result << std::endl;
}