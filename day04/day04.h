#ifndef AOC2024_DAY04_H
#define AOC2024_DAY04_H

#include "../lib/grid.h"

namespace day4 {

std::shared_ptr<aoc::Grid> parse_input(std::ifstream &input);

int part1(const aoc::Grid &grid);

int part2(const aoc::Grid &grid);

} // namespace day4

#endif // AOC2024_DAY04_H