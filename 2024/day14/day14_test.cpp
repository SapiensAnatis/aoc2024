#include "../lib/aoc.h"
#include "day14.h"
#include "gtest/gtest.h"

TEST(day14_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day14);
    const auto input = day14::parse_input(input_stream);

    std::shared_ptr grid = aoc::Grid::create('.', 11, 7);

    auto result = day14::puzzle_part1(input, grid);

    std::cout << result << std::endl;
}

TEST(day14_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day14);
    const auto input = day14::parse_input(input_stream);

    auto result = day14::part1(input);

    std::cout << result << std::endl;
}

TEST(day14_part2, example) {
    // N/A, example input will not make a Christmas tree
}

TEST(day14_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day14);
    const auto input = day14::parse_input(input_stream);

    int result = day14::part2(input);

    std::cout << result << std::endl;
}
