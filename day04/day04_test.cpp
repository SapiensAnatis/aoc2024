#include <fstream>

#include "../lib/aoc.h"
#include "day04.h"
#include "gtest/gtest.h"

using namespace day4;

TEST(day04_part1, example) {
    std::ifstream input_stream = aoc::get_example_ifstream();

    auto grid = parse_input(input_stream);
    // this deref is probably horrible but im too lazy to fix the impl to take
    // a shared_ptr
    int count = part1(*grid);

    std::cout << count << std::endl;
}

TEST(day04_part1, real) {
    std::ifstream input_stream = aoc::get_real_ifstream();

    auto grid = parse_input(input_stream);
    int count = part1(*grid);

    std::cout << count << std::endl;
}

TEST(day04_part2, example) {
    std::ifstream input_stream = aoc::get_example_ifstream();

    auto grid = parse_input(input_stream);
    int count = part2(*grid);

    std::cout << count << std::endl;
}

TEST(day04_part2, real) {
    std::ifstream input_stream = aoc::get_real_ifstream();

    auto grid = parse_input(input_stream);
    int count = part2(*grid);

    std::cout << count << std::endl;
}