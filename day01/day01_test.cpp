#include "day01.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace day1;

TEST(day_1_part_1, example) {
    auto input = parse_input("/home/jay/Projects/aoc2024/day01/example.txt");
    auto result = part1(input);
    std::cout << result << "\n";
}

TEST(day_1_part_1, real) {
    auto input = parse_input("/home/jay/Projects/aoc2024/day01/input.txt");
    auto result = part1(input);
    std::cout << result << "\n";
}

TEST(day_1_part_2, example) {
    auto input = parse_input("/home/jay/Projects/aoc2024/day01/example.txt");
    auto result = part2(input);
    std::cout << result << "\n";
}

TEST(day_1_part_2, real) {
    auto input = parse_input("/home/jay/Projects/aoc2024/day01/input.txt");
    auto result = part2(input);
    std::cout << result << "\n";
}