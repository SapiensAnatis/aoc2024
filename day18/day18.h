#ifndef AOC2024_DAY18_H
#define AOC2024_DAY18_H

#include "../lib/grid.h"
#include <vector>

namespace day18 {

struct ParsedInput {
    std::vector<aoc::Point> byte_positions;
};

ParsedInput parse_input(std::ifstream &input_stream);

int puzzle_part1(const ParsedInput &input, int grid_size, int num_bytes_fall);

int part1(const ParsedInput &input);

aoc::Point puzzle_part2(const ParsedInput &input, int grid_size, int num_bytes_fall);

aoc::Point part2(const ParsedInput &input);

} // namespace day18

#endif // AOC2024_DAY18_H
