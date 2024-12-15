#include "../lib/aoc.h"
#include "day11.h"
#include "gtest/gtest.h"

TEST(day11_part1, example) {
    auto input_stream = aoc::get_example_ifstream();

    auto input = day11::parse_input(input_stream);

    int result = day11::part1(input, 6);

    std::cout << result << "\n";
}

TEST(day11_part1, real) {
    auto input_stream = aoc::get_real_ifstream();

    auto input = day11::parse_input(input_stream);

    int result = day11::part1(input, 25);

    std::cout << result << "\n";
}

TEST(day11_part2, example) {
    auto input_stream = aoc::get_example_ifstream();

    auto input = day11::parse_input(input_stream);

    long result = day11::part2(input, 6);

    std::cout << result << "\n";
}

TEST(day11_part2, example_part1_real) {
    auto input_stream = aoc::get_real_ifstream();

    auto input = day11::parse_input(input_stream);

    long result = day11::part2(input, 25);

    std::cout << result << "\n";
}

TEST(day11_part2, real) {
    auto input_stream = aoc::get_real_ifstream();

    auto input = day11::parse_input(input_stream);

    long result = day11::part2(input, 75);

    std::cout << result << "\n";
}
