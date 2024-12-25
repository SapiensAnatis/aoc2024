#include "../lib/aoc.h"
#include "day17.h"
#include "gtest/gtest.h"

TEST(day17_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day17::parse_input(input_stream);

    day17::part1(input);
}

TEST(day17_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day17::parse_input(input_stream);

    day17::part1(input);
}

TEST(day17_part2, example) {
    auto input_stream = aoc::get_example_ifstream(2);
    auto input = day17::parse_input(input_stream);

    auto result = day17::part2(input);

    std::cout << result << std::endl;
}

TEST(day17_part2, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day17::parse_input(input_stream);

    auto result = day17::part2(input);

    std::cout << result << std::endl;
}
