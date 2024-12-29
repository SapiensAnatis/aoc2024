#include "../lib/aoc.h"
#include "day12.h"
#include "gtest/gtest.h"

TEST(day12_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day12);

    auto input = day12::parse_input(input_stream);

    int result = day12::part1(input);

    std::cout << result << std::endl;
}

TEST(day12_part1, example2) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day12, 2);

    auto input = day12::parse_input(input_stream);

    int result = day12::part1(input);

    std::cout << result << std::endl;
}

TEST(day12_part1, example3) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day12, 3);

    auto input = day12::parse_input(input_stream);

    int result = day12::part1(input);

    std::cout << result << std::endl;
}

TEST(day12_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day12);

    auto input = day12::parse_input(input_stream);

    int result = day12::part1(input);

    std::cout << result << std::endl;
}

TEST(day12_part2, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day12);

    auto input = day12::parse_input(input_stream);

    int result = day12::part2(input);

    std::cout << result << std::endl;
}

TEST(day12_part2, example2) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day12, 2);

    auto input = day12::parse_input(input_stream);

    int result = day12::part2(input);

    std::cout << result << std::endl;
}

TEST(day12_part2, example3) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day12, 4);

    auto input = day12::parse_input(input_stream);

    int result = day12::part2(input);

    std::cout << result << std::endl;
}

TEST(day12_part2, example4) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day12, 5);

    auto input = day12::parse_input(input_stream);

    int result = day12::part2(input);

    std::cout << result << std::endl;
}

TEST(day12_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day12);

    auto input = day12::parse_input(input_stream);

    int result = day12::part2(input);

    std::cout << result << std::endl;
}
