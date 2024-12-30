#include "../lib/aoc.h"
#include "day17.h"
#include "gtest/gtest.h"

TEST(day17_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day17);
    auto input = day17::parse_input(input_stream);

    day17::part1(input);
}

TEST(day17_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day17);
    auto input = day17::parse_input(input_stream);

    auto result = day17::part1(input);

    std::cout << result << std::endl;
}

TEST(day17_part2, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day17, 2);
    auto input = day17::parse_input(input_stream);

    auto result = day17::part2(input);

    std::cout << result << std::endl;
}

TEST(day17_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day17);
    auto input = day17::parse_input(input_stream);

    auto result = day17::part2(input);

    std::cout << result << std::endl;
}

TEST(day17_part2, p1p2) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day17);
    auto input = day17::parse_input(input_stream);

    auto result1 = day17::part1(input);
    auto result2 = day17::part2(input);

    std::cout << result1 << std::endl;
    std::cout << result2 << std::endl;
}
