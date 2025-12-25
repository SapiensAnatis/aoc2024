#include "../lib/aoc.h"
#include "day03.h"
#include "gtest/gtest.h"
#include <fstream>

using namespace day03;

TEST(day03_part1, example) {
    std::ifstream input_stream = aoc::get_example_ifstream(aoc::Day03);

    ParsedInput parsed = parse_input(input_stream);
    int result = part1(parsed);

    std::cout << result << std::endl;
}

TEST(day03_part1, real) {
    std::ifstream input_stream = aoc::get_real_ifstream(aoc::Day03);

    ParsedInput parsed = parse_input(input_stream);
    int result = part1(parsed);

    std::cout << result << std::endl;
}

TEST(day03_part2, example) {
    std::ifstream input_stream = aoc::get_example_ifstream(aoc::Day03);

    ParsedInput parsed = parse_input(input_stream);
    int result = part2(parsed);

    std::cout << result << std::endl;
}

TEST(day03_part2, real) {
    std::ifstream input_stream = aoc::get_real_ifstream(aoc::Day03);

    ParsedInput parsed = parse_input(input_stream);
    int result = part2(parsed);

    std::cout << result << std::endl;
}