#include "../lib/aoc.h"
#include "day7.h"
#include "gtest/gtest.h"

TEST(day_7_part_1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day7::parse_input(input_stream);

    int result = 0;

    std::cout << result << "\n";
}