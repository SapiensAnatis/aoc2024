#include "../lib/aoc.h"
#include "day21.h"
#include "gtest/gtest.h"

TEST(day21_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day21::parse_input(input_stream);

    auto result = day21::part1(input);

    std::cout << result << std::endl;
}

TEST(day12_part1, decompile) {
    auto step3_input =
        "<v<A>>^AvA^A<vA<AA>>^AAvA<^A>AAvA^A<vA>^AA<A>A<v<A>A>^AAAvA<^A>A";
    auto step2_input = day21::decompile_dpad_input(step3_input);
    auto step1_input = day21::decompile_dpad_input(step2_input);
    std::cout << step1_input << std::endl;
    std::cout << step2_input << std::endl;
    std::cout << step3_input << std::endl;
}

TEST(day21_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day21::parse_input(input_stream);

    auto result = day21::part1(input);

    std::cout << result << std::endl;
}

TEST(day21_part2, example) {}

TEST(day21_part2, real) {}
