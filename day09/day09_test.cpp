#include "../lib/aoc.h"
#include "day09.h"
#include "gtest/gtest.h"

TEST(day09_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day9::parse_input(input_stream);

    long result = day9::part1(input);

    std::cout << result << std::endl;
}

TEST(day09_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day9::parse_input(input_stream);

    long result = day9::part1(input);

    std::cout << result << std::endl;
}

TEST(day09_part2, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day9::parse_input(input_stream);

    long result = day9::part2(input);

    std::cout << result << std::endl;
}

TEST(day09_part2, example2) {
    auto input_stream = aoc::get_example_ifstream(2);
    auto input = day9::parse_input(input_stream);

    long result = day9::part2(input);

    std::cout << result << std::endl;
}

TEST(day09_part2, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day9::parse_input(input_stream);

    long result = day9::part2(input);

    std::cout << result << std::endl;
}
