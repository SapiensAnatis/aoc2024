#ifndef AOC2024_DAY06_H
#define AOC2024_DAY06_H

#include "../lib/grid.h"

namespace day06 {

struct ParsedInput {
    std::shared_ptr<aoc::Grid> grid;
    aoc::Point guard_start_point;

    ParsedInput(std::shared_ptr<aoc::Grid> grid, aoc::Point guard_start_point);
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);

} // namespace day6

#endif // AOC2024_DAY06_H