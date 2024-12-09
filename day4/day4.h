#ifndef AOC2024_DAY4_H
#define AOC2024_DAY4_H

#include "../lib/aoc.h"

namespace day4 {

aoc::Grid parse_input(std::ifstream &input);

int part1(const aoc::Grid &grid);

int part2(const aoc::Grid &grid);

} // namespace day4

#endif // AOC2024_DAY4_H