#ifndef AOC2024_DAY20_H
#define AOC2024_DAY20_H
#include "../lib/grid.h"
#include <memory>

namespace day20 {

struct ParsedInput {
    std::unique_ptr<aoc::Grid> grid;
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);

} // namespace day20

#endif // AOC2024_DAY20_H
