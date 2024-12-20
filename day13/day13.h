#ifndef AOC2024_DAY13_H
#define AOC2024_DAY13_H

#include "../lib/grid.h"

namespace day13 {

struct ClawMachine {
    aoc::Vector a_button;
    aoc::Vector b_button;
    aoc::Point prize_location;
};

struct ParsedInput {
    std::vector<ClawMachine> claw_machines;
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);

long part2(const ParsedInput &input);

} // namespace day13

#endif // AOC2024_DAY13_H
