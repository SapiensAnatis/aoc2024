#include "../lib/aoc.h"
#include "day07.h"
#include "gtest/gtest.h"

TEST(day07_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day7::parse_input(input_stream);

    long result = day7::part1(input);

    std::cout << result << "\n";
}

TEST(day07_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day7::parse_input(input_stream);

    long result = day7::part1(input);

    std::cout << result << "\n";
}

TEST(day07_part2, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day7::parse_input(input_stream);

    long result = day7::part2(input);

    std::cout << result << "\n";
}

TEST(day07_part2, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day7::parse_input(input_stream);

    long result = day7::part2(input);

    std::cout << result << "\n";
}