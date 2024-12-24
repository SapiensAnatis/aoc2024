#ifndef AOC2024_DAY15_H
#define AOC2024_DAY15_H

#include "../lib/grid.h"
#include <fstream>

namespace day15 {

struct ParsedInput {
    std::unique_ptr<aoc::Grid> grid;
    std::vector<aoc::Direction> moves;
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(ParsedInput &input);

} // namespace day15

#endif // AOC2024_DAY15_H
