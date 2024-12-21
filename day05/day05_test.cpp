#include <fstream>

#include "../lib/aoc.h"
#include "day05.h"
#include "gtest/gtest.h"

using namespace day5;

TEST(day05_part1, example) {
    std::ifstream input_stream = aoc::get_example_ifstream();

    auto input = parse_input(input_stream);
    auto result = part1(input);

    std::cout << result << std::endl;
}

TEST(day05_part1, real) {
    std::ifstream input_stream = aoc::get_real_ifstream();

    auto input = parse_input(input_stream);
    auto result = part1(input);

    std::cout << result << std::endl;
}

TEST(day05_part2, example) {
    std::ifstream input_stream = aoc::get_example_ifstream();

    auto input = parse_input(input_stream);
    auto result = part2(input);

    std::cout << result << std::endl;
}

TEST(day05_part2, real) {
    std::ifstream input_stream = aoc::get_real_ifstream();

    auto input = parse_input(input_stream);
    auto result = part2(input);

    std::cout << result << std::endl;
}