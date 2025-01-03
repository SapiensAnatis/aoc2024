#include "../lib/aoc.h"
#include "day15.h"
#include "gtest/gtest.h"

TEST(day15_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day15);
    auto input = day15::parse_input(input_stream);

    auto result = day15::part1(input);

    std::cout << result << std::endl;
}

TEST(day15_part1, example2) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day15, 2);
    auto input = day15::parse_input(input_stream);

    auto result = day15::part1(input);

    std::cout << result << std::endl;
}

TEST(day15_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day15);
    auto input = day15::parse_input(input_stream);

    auto result = day15::part1(input);

    std::cout << result << std::endl;
}

TEST(day15_part2, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day15, 3);
    auto input = day15::parse_input(input_stream);

    auto result = day15::part2(input);

    std::cout << result << std::endl;
}

TEST(day15_part2, example2) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day15, 2);
    auto input = day15::parse_input(input_stream);

    auto result = day15::part2(input);

    std::cout << result << std::endl;
}

TEST(day15_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day15);
    auto input = day15::parse_input(input_stream);

    auto result = day15::part2(input);

    std::cout << result << std::endl;
}
