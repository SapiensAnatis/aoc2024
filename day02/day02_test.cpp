//
// Created by jay on 03/12/24.
//

#include "../lib/aoc.h"
#include "day02.h"
#include "gtest/gtest.h"

TEST(day_2_part_1, example) {
    std::ifstream input = aoc::get_example_ifstream();
    auto parsed = day2::parse_input(input);
    auto result = day2::part1(parsed);
    std::cout << result << "\n";
}

TEST(day_2_part_1, real) {
    std::ifstream input = aoc::get_real_ifstream();
    auto parsed = day2::parse_input(input);
    auto result = day2::part1(parsed);
    std::cout << result << "\n";
}

TEST(day_2_part_2, example) {
    std::ifstream input = aoc::get_example_ifstream();
    auto parsed = day2::parse_input(input);
    auto result = day2::part2(parsed);
    std::cout << result << "\n";
}

TEST(day_2_part_2, real) {
    std::ifstream input = aoc::get_real_ifstream();
    auto parsed = day2::parse_input(input);
    auto result = day2::part2(parsed);
    std::cout << result << "\n";
}
