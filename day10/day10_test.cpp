#include "../lib/aoc.h"
#include "day10.h"
#include "gtest/gtest.h"

TEST(day10_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day10);
    auto input = day10::parse_input(input_stream);

    long result = day10::part1(input);

    std::cout << result << std::endl;
}

TEST(day10_part1, example2) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day10, 2);
    auto input = day10::parse_input(input_stream);

    long result = day10::part1(input);

    std::cout << result << std::endl;
}

TEST(day10_part1, example3) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day10, 3);
    auto input = day10::parse_input(input_stream);

    long result = day10::part1(input);

    std::cout << result << std::endl;
}

TEST(day10_part1, example4) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day10, 4);
    auto input = day10::parse_input(input_stream);

    long result = day10::part1(input);

    std::cout << result << std::endl;
}

TEST(day10_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day10);
    auto input = day10::parse_input(input_stream);

    long result = day10::part1(input);

    std::cout << result << std::endl;
}

TEST(day10_part2, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day10, 5);
    auto input = day10::parse_input(input_stream);

    long result = day10::part2(input);

    std::cout << result << std::endl;
}

TEST(day10_part2, example2) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day10, 6);
    auto input = day10::parse_input(input_stream);

    long result = day10::part2(input);

    std::cout << result << std::endl;
}

TEST(day10_part2, example3) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day10, 4);
    auto input = day10::parse_input(input_stream);

    long result = day10::part2(input);

    std::cout << result << std::endl;
}

TEST(day10_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day10);
    auto input = day10::parse_input(input_stream);

    long result = day10::part2(input);

    std::cout << result << std::endl;
}
