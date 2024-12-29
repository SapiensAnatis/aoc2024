#include "../lib/aoc.h"
#include "day06.h"
#include "gtest/gtest.h"
#include <chrono>

TEST(day06_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day6::parse_input(input_stream);

    int result = day6::part1(input);

    std::cout << result << std::endl;
}

TEST(day06_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day6::parse_input(input_stream);

    int result = day6::part1(input);

    std::cout << result << std::endl;
}

TEST(day06_part2, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day6::parse_input(input_stream);

    int result = day6::part2(input);

    std::cout << result << std::endl;
}

TEST(day06_part2, real) {
    auto t1 = std::chrono::high_resolution_clock::now();

    auto input_stream = aoc::get_real_ifstream();
    auto input = day6::parse_input(input_stream);

    int result = day6::part2(input);

    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << result << std::endl;
    std::cout << "Execution time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) << std::endl;
}