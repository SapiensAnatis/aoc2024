#ifndef AOC2024_DAY6_H
#define AOC2024_DAY6_H

#include "../lib/aoc.h"

namespace day6 {
struct ParsedInput {
    aoc::Grid grid;
    aoc::Point guard_start_point;

    ParsedInput(aoc::Grid grid, aoc::Point guard_start_point);
};

ParsedInput parse_input(std::ifstream &input_stream);
} // namespace day6

#endif // AOC2024_DAY6_H