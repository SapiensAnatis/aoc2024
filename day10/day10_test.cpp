#include "../lib/aoc.h"
#include "day10.h"
#include "gtest/gtest.h"

TEST(day_10_part_1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day10::parse_input(input_stream);

    long result = day10::part1(input);

    std::cout << result << "\n";
}

TEST(day_10_part_1, example2) {
    auto input_stream = aoc::get_example_ifstream(2);
    auto input = day10::parse_input(input_stream);

    long result = day10::part1(input);

    std::cout << result << "\n";
}

TEST(day_10_part_1, example3) {
    auto input_stream = aoc::get_example_ifstream(3);
    auto input = day10::parse_input(input_stream);

    long result = day10::part1(input);

    std::cout << result << "\n";
}

TEST(day_10_part_1, example4) {
    auto input_stream = aoc::get_example_ifstream(4);
    auto input = day10::parse_input(input_stream);

    long result = day10::part1(input);

    std::cout << result << "\n";
}

TEST(day_10_part_1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day10::parse_input(input_stream);

    long result = day10::part1(input);

    std::cout << result << "\n";
}

TEST(day_10_part_2, example) {
    auto input_stream = aoc::get_example_ifstream(5);
    auto input = day10::parse_input(input_stream);

    long result = day10::part2(input);

    std::cout << result << "\n";
}

TEST(day_10_part_2, example2) {
    auto input_stream = aoc::get_example_ifstream(6);
    auto input = day10::parse_input(input_stream);

    long result = day10::part2(input);

    std::cout << result << "\n";
}

TEST(day_10_part_2, example3) {
    auto input_stream = aoc::get_example_ifstream(4);
    auto input = day10::parse_input(input_stream);

    long result = day10::part2(input);

    std::cout << result << "\n";
}

TEST(day_10_part_2, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day10::parse_input(input_stream);

    long result = day10::part2(input);

    std::cout << result << "\n";
}