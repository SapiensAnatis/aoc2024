#include "../lib/aoc.h"
#include "day07.h"
#include "gtest/gtest.h"

TEST(day07_part1, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    long result = day07::part1(input);

    std::cout << result << std::endl;
}

TEST(day07_part1, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    long result = day07::part1(input);

    std::cout << result << std::endl;
}

TEST(day07_part2, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    long result = day07::part2(input);

    std::cout << result << std::endl;
}

TEST(day07_part2, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    long result = day07::part2(input);

    std::cout << result << std::endl;
}

TEST(day07_part1_faster, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    long result = day07::part1(input);
    long faster_result = day07::faster::part1(input);

    ASSERT_EQ(faster_result, result);
}

TEST(day07_part1_faster, perf) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    aoc::time_execution("day07_part1 original", [&input] { day07::part1(input); });
    aoc::time_execution("day07_part1 faster", [&input] { day07::faster::part1(input); });
}

TEST(day07_part2_faster, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    long result = day07::faster::part2(input);

    ASSERT_EQ(result, 11387);
}

TEST(day07_part2_faster, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    long result = day07::part2(input);
    long faster_result = day07::faster::part2(input);

    ASSERT_EQ(faster_result, result);
}

TEST(day07_part2_faster, perf) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day07);
    auto input = day07::parse_input(input_stream);

    aoc::time_execution("day07_part2 original", [&input] { day07::part2(input); });
    aoc::time_execution("day07_part2 faster", [&input] { day07::faster::part2(input); });
}