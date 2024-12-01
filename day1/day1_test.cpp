#include "gtest/gtest.h"
#include "day1.h"
#include <iostream>

TEST(part1, example){
    auto input = parse_input("/home/jay/Projects/aoc2024/day1/example.txt");
    auto result = part1(input);
    std::cout << result << "\n";
}

TEST(part1, real){
    auto input = parse_input("/home/jay/Projects/aoc2024/day1/input.txt");
    auto result = part1(input);
    std::cout << result << "\n";
}

TEST(part2, example){
    auto input = parse_input("/home/jay/Projects/aoc2024/day1/example.txt");
    auto result = part2(input);
    std::cout << result << "\n";
}

TEST(part2, real){
    auto input = parse_input("/home/jay/Projects/aoc2024/day1/input.txt");
    auto result = part2(input);
    std::cout << result << "\n";
}