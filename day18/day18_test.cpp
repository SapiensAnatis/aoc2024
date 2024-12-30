#include "../lib/aoc.h"
#include "day18.h"
#include "gtest/gtest.h"

TEST(day18_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day18);
    auto input = day18::parse_input(input_stream);

    int grid_size = 7;
    int num_bytes = 12;

    auto result = day18::puzzle_part1(input, grid_size, num_bytes);

    std::cout << result << std::endl;
}

TEST(day18_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day18);
    auto input = day18::parse_input(input_stream);

    auto result = day18::part1(input);

    std::cout << result << std::endl;
}

TEST(day18_part2, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day18);
    auto input = day18::parse_input(input_stream);

    int grid_size = 7;
    int num_bytes = 12;

    auto result = day18::puzzle_part2(input, grid_size, num_bytes);

    std::cout << result << std::endl;
}

TEST(day18_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day18);
    auto input = day18::parse_input(input_stream);

    auto result = day18::part2(input);

    std::cout << result << std::endl;
}
