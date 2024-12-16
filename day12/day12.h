#ifndef AOC2024_day12_H
#define AOC2024_day12_H

#include "../lib/grid.h"
#include <memory>

namespace day12 {

struct ParsedInput {
    std::unique_ptr<aoc::Grid> grid;
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);

} // namespace day12

#endif // AOC2024_day12_H
