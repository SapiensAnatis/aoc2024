#include "../lib/aoc.h"
#include "day13.h"
#include "gtest/gtest.h"
#include <chrono>

TEST(day13_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day13);
    const auto input = day13::parse_input(input_stream);

    auto result = day13::part1(input);

    std::cout << result << std::endl;
}

TEST(day13_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day13);
    const auto input = day13::parse_input(input_stream);

    auto result = day13::part1(input);

    std::cout << result << std::endl;
}

TEST(day13_part1, perf) {
    auto t1 = std::chrono::high_resolution_clock::now();

    auto input_stream = aoc::get_real_ifstream(aoc::Day13);
    auto input = day13::parse_input(input_stream);

    auto result = day13::part1(input);

    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << result << std::endl;
    std::cout << "Execution time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1) << std::endl;
}

TEST(day13_part2, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day13);
    const auto input = day13::parse_input(input_stream);

    auto result = day13::part2(input);

    std::cout << result << std::endl;
}

TEST(day13_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day13);
    const auto input = day13::parse_input(input_stream);

    auto result = day13::part2(input);

    std::cout << result << std::endl;
}
