#include "day01.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace day1;

TEST(day01_part1, example) {
    auto input = parse_input("/home/jay/Projects/aoc2024/day01/example.txt");
    auto result = part1(input);
    std::cout << result << "\n";
}

TEST(day01_part1, real) {
    auto input = parse_input("/home/jay/Projects/aoc2024/day01/input.txt");
    auto result = part1(input);
    std::cout << result << "\n";
}

TEST(day01_part2, example) {
    auto input = parse_input("/home/jay/Projects/aoc2024/day01/example.txt");
    auto result = part2(input);
    std::cout << result << "\n";
}

TEST(day01_part2, real) {
    auto input = parse_input("/home/jay/Projects/aoc2024/day01/input.txt");
    auto result = part2(input);
    std::cout << result << "\n";
}