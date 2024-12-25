#ifndef AOC2024_DAY16_H
#define AOC2024_DAY16_H

#include "../lib/grid.h"

namespace day16 {

struct ParsedInput {
    std::unique_ptr<aoc::Grid> grid;
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);
int part2(const ParsedInput &input);

} // namespace day16

#endif // AOC2024_DAY16_H
