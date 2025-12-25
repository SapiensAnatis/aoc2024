#ifndef AOC2024_DAY10_H
#define AOC2024_DAY10_H

#include "../lib/grid.h"
#include <memory>

namespace day10 {

struct ParsedInput {
    std::unique_ptr<aoc::Grid> grid;
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);

} // namespace day10

#endif // AOC2024_DAY10_H
