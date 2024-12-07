#include <fstream>

#include "../lib/aoc.h"
#include "day4.h"
#include "gtest/gtest.h"

using namespace day4;

TEST(day_4_part_1, example) {
    std::ifstream input_stream = aoc::get_example_ifstream();

    Grid grid = parse_input(input_stream);
    int count = part1(grid);

    std::cout << count << "\n";
}

TEST(day_4_part_1, real) {
    std::ifstream input_stream = aoc::get_real_ifstream();

    Grid grid = parse_input(input_stream);
    int count = part1(grid);

    std::cout << count << "\n";
}

TEST(day_4_part_2, example) {
    std::ifstream input_stream = aoc::get_example_ifstream();

    Grid grid = parse_input(input_stream);
    int count = part2(grid);

    std::cout << count << "\n";
}

TEST(day_4_part_2, real) {
    std::ifstream input_stream = aoc::get_real_ifstream();

    Grid grid = parse_input(input_stream);
    int count = part2(grid);

    std::cout << count << "\n";
}