#include "../lib/aoc.h"
#include "day03.h"
#include "gtest/gtest.h"
#include <fstream>

using namespace day3;

TEST(day03_part1, example) {
    std::ifstream input_stream = aoc::get_example_ifstream();

    ParsedInput parsed = parse_input(input_stream);
    int result = part1(parsed);

    std::cout << result << std::endl;
}

TEST(day03_part1, real) {
    std::ifstream input_stream = aoc::get_real_ifstream();

    ParsedInput parsed = parse_input(input_stream);
    int result = part1(parsed);

    std::cout << result << std::endl;
}

TEST(day03_part2, example) {
    std::ifstream input_stream = aoc::get_example_ifstream(2);

    ParsedInput parsed = parse_input(input_stream);
    int result = part2(parsed);

    std::cout << result << std::endl;
}

TEST(day03_part2, real) {
    std::ifstream input_stream = aoc::get_real_ifstream();

    ParsedInput parsed = parse_input(input_stream);
    int result = part2(parsed);

    std::cout << result << std::endl;
}