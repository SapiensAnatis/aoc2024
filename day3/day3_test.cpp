#include "day3.h"
#include "gtest/gtest.h"
#include "../lib/aoc.h"
#include <fstream>

using namespace day3;

TEST(day_3_part_1, example) {
    std::ifstream input_stream = aoc::get_example_ifstream();

    ParsedInput parsed = parse_input(input_stream);
    int result = part1(parsed);

    std::cout << result << "\n";
}

TEST(day_3_part_1, real) {
    std::ifstream input_stream = aoc::get_real_ifstream();

    ParsedInput parsed = parse_input(input_stream);
    int result = part1(parsed);

    std::cout << result << "\n";
}

TEST(day_3_part_2, example) {
    std::ifstream input_stream = aoc::get_example_ifstream(2);

    ParsedInput parsed = parse_input(input_stream);
    int result = part2(parsed);

    std::cout << result << "\n";
}

TEST(day_3_part_2, real) {
    std::ifstream input_stream = aoc::get_real_ifstream();

    ParsedInput parsed = parse_input(input_stream);
    int result = part2(parsed);

    std::cout << result << "\n";
}