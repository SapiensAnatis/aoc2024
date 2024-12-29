#include "../lib/aoc.h"
#include "day01.h"

#include "gtest/gtest.h"
#include <iostream>

using namespace day1;

TEST(day01_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day01);
    auto input = parse_input(input_stream);
    auto result = part1(input);
    std::cout << result << std::endl;
}

TEST(day01_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day01);
    auto input = parse_input(input_stream);
    auto result = part1(input);
    std::cout << result << std::endl;
}

TEST(day01_part2, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day01);
    auto input = parse_input(input_stream);
    auto result = part2(input);
    std::cout << result << std::endl;
}

TEST(day01_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day01);
    auto input = parse_input(input_stream);
    auto result = part2(input);
    std::cout << result << std::endl;
}