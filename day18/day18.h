#ifndef AOC2024_DAY18_H
#define AOC2024_DAY18_H

#include "../lib/grid.h"
#include <vector>

namespace day18 {

struct ParsedInput {
    std::vector<aoc::Point> byte_positions;
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input, int grid_size, int num_bytes_fall);

} // namespace day18

#endif // AOC2024_DAY18_H
