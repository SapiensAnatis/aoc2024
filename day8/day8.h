#ifndef AOC2024_DAY8_H
#define AOC2024_DAY8_H

#include "../lib/grid.h"
#include <memory>

namespace day8 {

struct ParsedInput {
    explicit ParsedInput(std::unique_ptr<aoc::Grid> grid);

    std::unique_ptr<aoc::Grid> grid;
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);

} // namespace day8

#endif // AOC2024_DAY8_H