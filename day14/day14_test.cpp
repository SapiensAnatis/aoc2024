#include "../lib/aoc.h"
#include "day14.h"
#include "gtest/gtest.h"

TEST(day14_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    std::shared_ptr<aoc::Grid> grid = aoc::Grid::create('.', 11, 7);
    const auto input = day14::parse_input(input_stream, grid);

    auto result = day14::part1(input);

    std::cout << result << std::endl;
}

TEST(day14_part1, real) {}

TEST(day14_part2, example) {}

TEST(day14_part2, real) {}
