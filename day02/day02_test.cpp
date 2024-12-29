//
// Created by jay on 03/12/24.
//

#include "../lib/aoc.h"
#include "day02.h"
#include "gtest/gtest.h"

TEST(day02_part1, example) {
    std::ifstream input = aoc::get_example_ifstream(aoc::Day02);
    auto parsed = day2::parse_input(input);
    auto result = day2::part1(parsed);
    std::cout << result << std::endl;
}

TEST(day02_part1, real) {
    std::ifstream input = aoc::get_real_ifstream(aoc::Day02);
    auto parsed = day2::parse_input(input);
    auto result = day2::part1(parsed);
    std::cout << result << std::endl;
}

TEST(day02_part2, example) {
    std::ifstream input = aoc::get_example_ifstream(aoc::Day02);
    auto parsed = day2::parse_input(input);
    auto result = day2::part2(parsed);
    std::cout << result << std::endl;
}

TEST(day02_part2, real) {
    std::ifstream input = aoc::get_real_ifstream(aoc::Day02);
    auto parsed = day2::parse_input(input);
    auto result = day2::part2(parsed);
    std::cout << result << std::endl;
}
