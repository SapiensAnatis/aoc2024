#include <fstream>

#include "day5.h"
#include "../lib/aoc.h"
#include "gtest/gtest.h"

using namespace day5;

TEST(day_5_part_1, example) {
    std::ifstream input_stream = aoc::get_example_ifstream();

    auto input = parse_input(input_stream);
    auto result = part1(input);

    std::cout << result << "\n";
}

TEST(day_5_part_1, real) {
    std::ifstream input_stream = aoc::get_real_ifstream();

    auto input = parse_input(input_stream);
    auto result = part1(input);

    std::cout << result << "\n";
}


TEST(day_5_part_2, example) {
    std::ifstream input_stream = aoc::get_example_ifstream();

    auto input = parse_input(input_stream);
    auto result = part2(input);

    std::cout << result << "\n";
}

TEST(day_5_part_2, real) {
    std::ifstream input_stream = aoc::get_real_ifstream();

    auto input = parse_input(input_stream);
    auto result = part2(input);

    std::cout << result << "\n";
}