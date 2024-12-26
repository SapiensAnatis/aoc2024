#include "../lib/aoc.h"
#include "day19.h"
#include "gtest/gtest.h"

TEST(day19_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day19::parse_input(input_stream);

    auto result = day19::part1(input);

    std::cout << result << std::endl;
}

TEST(day19_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day19::parse_input(input_stream);

    auto result = day19::part1(input);

    std::cout << result << std::endl;
}

TEST(day19_part2, example) {
    // this is too slow with recursion, need a better algo
    // idea: bfs but tracking the path on each node
    auto input_stream = aoc::get_example_ifstream();
    auto input = day19::parse_input(input_stream);

    auto result = day19::part2(input);

    std::cout << result << std::endl;
}

TEST(day19_part2, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day19::parse_input(input_stream);

    auto result = day19::part2(input);

    std::cout << result << std::endl;
}
