#include "../lib/aoc.h"
#include "day6.h"
#include "gtest/gtest.h"
#include <chrono>

TEST(day_6_part_1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day6::parse_input(input_stream);

    int result = day6::part1(input);

    std::cout << result << "\n";
}

TEST(day_6_part_1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day6::parse_input(input_stream);

    int result = day6::part1(input);

    std::cout << result << "\n";
}

TEST(day_6_part_2, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day6::parse_input(input_stream);

    int result = day6::part2(input);

    std::cout << result << "\n";
}

TEST(day_6_part_2, real) {
    auto t1 = std::chrono::high_resolution_clock::now();

    auto input_stream = aoc::get_real_ifstream();
    auto input = day6::parse_input(input_stream);

    int result = day6::part2(input);
    
    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << result << "\n";
    std::cout << "Execution time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
              << "\n";
}