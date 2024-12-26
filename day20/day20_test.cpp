#include "../lib/aoc.h"
#include "day20.h"
#include "gtest/gtest.h"

TEST(day20_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day20::parse_input(input_stream);

    auto result = day20::part1(input);

    std::cout << result << std::endl;
}

TEST(day20_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day20::parse_input(input_stream);

    auto result = day20::part1(input);

    std::cout << result << std::endl;
}

TEST(day20_part2, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day20::parse_input(input_stream);

    auto result = day20::part2(input);

    std::cout << result << std::endl;
}

TEST(day20_part2, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day20::parse_input(input_stream);

    auto result = day20::part2(input);

    std::cout << result << std::endl;
}
