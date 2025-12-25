#include <fstream>

#include "../lib/aoc.h"
#include "day04.h"
#include "gtest/gtest.h"

using namespace day04;

TEST(day04_part1, example) {
    std::ifstream input_stream = aoc::get_example_ifstream(aoc::Day04);

    auto input = parse_input(input_stream);
    int count = part1(input);

    std::cout << count << std::endl;
}

TEST(day04_part1, real) {
    std::ifstream input_stream = aoc::get_real_ifstream(aoc::Day04);

    auto input = parse_input(input_stream);
    int count = part1(input);

    std::cout << count << std::endl;
}

TEST(day04_part2, example) {
    std::ifstream input_stream = aoc::get_example_ifstream(aoc::Day04);

    auto input = parse_input(input_stream);
    int count = part2(input);

    std::cout << count << std::endl;
}

TEST(day04_part2, real) {
    std::ifstream input_stream = aoc::get_real_ifstream(aoc::Day04);

    auto input = parse_input(input_stream);
    int count = part2(input);

    std::cout << count << std::endl;
}