#include "../lib/aoc.h"
#include "day09.h"
#include "gtest/gtest.h"

TEST(day09_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day09);
    auto input = day09::parse_input(input_stream);

    long result = day09::part1(input);

    std::cout << result << std::endl;
}

TEST(day09_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day09);
    auto input = day09::parse_input(input_stream);

    long result = day09::part1(input);

    std::cout << result << std::endl;
}

TEST(day09_part2, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day09);
    auto input = day09::parse_input(input_stream);

    long result = day09::part2(input);

    std::cout << result << std::endl;
}

TEST(day09_part2, example2) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day09, 2);
    auto input = day09::parse_input(input_stream);

    long result = day09::part2(input);

    std::cout << result << std::endl;
}

TEST(day09_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day09);
    auto input = day09::parse_input(input_stream);

    long result = day09::part2(input);

    std::cout << result << std::endl;
}
