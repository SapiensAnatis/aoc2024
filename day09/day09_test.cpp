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

TEST(day09_part1_faster, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day09);
    auto input = day09::faster::parse_input(input_stream);

    long result = day09::faster::part1(input);

    ASSERT_EQ(result, 1928);
}

TEST(day09_part1_faster, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day09);
    auto input = day09::parse_input(input_stream);

    long result = day09::part1(input);

    input_stream = aoc::get_real_ifstream(aoc::Day09);
    auto faster_input = day09::faster::parse_input(input_stream);
    long faster_result = day09::faster::part1(faster_input);

    ASSERT_EQ(faster_result, result);
}

TEST(day09_part1_faster, perf) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day09);
    auto input = day09::parse_input(input_stream);

    input_stream = aoc::get_real_ifstream(aoc::Day09);
    auto faster_input = day09::faster::parse_input(input_stream);

    aoc::time_execution("day09_part1 original", [&input] { day09::part1(input); });
    aoc::time_execution("day09_part1 faster",
                        [&faster_input] { day09::faster::part1(faster_input); });
}

TEST(day09_part2_faster, example) {
    auto input_stream = aoc::get_example_ifstream(aoc::Day09);
    auto input = day09::faster::parse_input(input_stream);

    long result = day09::faster::part2(input);

    ASSERT_EQ(result, 2858);
}

TEST(day09_part2_faster, real) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day09);
    auto input = day09::parse_input(input_stream);

    long result = day09::part2(input);

    input_stream = aoc::get_real_ifstream(aoc::Day09);
    auto faster_input = day09::faster::parse_input(input_stream);
    long faster_result = day09::faster::part2(faster_input);

    ASSERT_EQ(faster_result, result);
}

TEST(day09_part2_faster, perf) {
    auto input_stream = aoc::get_real_ifstream(aoc::Day09);
    auto input = day09::parse_input(input_stream);

    input_stream = aoc::get_real_ifstream(aoc::Day09);
    auto faster_input = day09::faster::parse_input(input_stream);

    aoc::time_execution("day09_part2 original", [&input] { day09::part2(input); });
    aoc::time_execution("day09_part2 faster",
                        [&faster_input] { day09::faster::part2(faster_input); });
}
