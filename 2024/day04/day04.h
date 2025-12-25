#ifndef AOC2024_DAY04_H
#define AOC2024_DAY04_H

#include "../lib/grid.h"

namespace day04 {

struct ParsedInput {
    std::unique_ptr<aoc::Grid> grid;
};

ParsedInput parse_input(std::ifstream &input);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);

} // namespace day04

#endif // AOC2024_DAY04_H