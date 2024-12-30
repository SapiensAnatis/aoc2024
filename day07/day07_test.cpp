#include "../lib/aoc.h"
#include "day07.h"
#include "gtest/gtest.h"

TEST(day07_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    long result = day07::part1(input);

    std::cout << result << std::endl;
}

TEST(day07_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    long result = day07::part1(input);

    std::cout << result << std::endl;
}

TEST(day07_part2, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    long result = day07::part2(input);

    std::cout << result << std::endl;
}

TEST(day07_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    long result = day07::part2(input);

    std::cout << result << std::endl;
}