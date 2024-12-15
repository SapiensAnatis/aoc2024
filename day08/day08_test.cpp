#include "../lib/aoc.h"
#include "day08.h"
#include "gtest/gtest.h"

TEST(day08_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day8::parse_input(input_stream);

    int result = day8::part1(input);

    std::cout << result << std::endl;
}

TEST(day08_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day8::parse_input(input_stream);

    int result = day8::part1(input);

    std::cout << result << std::endl;
}

TEST(day08_part2, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day8::parse_input(input_stream);

    int result = day8::part2(input);

    std::cout << result << std::endl;
}

TEST(day08_part2, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day8::parse_input(input_stream);

    int result = day8::part2(input);

    std::cout << result << std::endl;
}