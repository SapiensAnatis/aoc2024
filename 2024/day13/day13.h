#ifndef AOC2024_DAY13_H
#define AOC2024_DAY13_H

#include "../lib/grid.h"

namespace day13 {

struct LongPoint {
    long x;
    long y;
};

struct ClawMachine {
    aoc::Vector a_button;
    aoc::Vector b_button;
    LongPoint prize_location;
};

struct ParsedInput {
    std::vector<ClawMachine> claw_machines;
};

ParsedInput parse_input(std::ifstream &input_stream);

long part1(const ParsedInput &input);

long part2(const ParsedInput &input);

} // namespace day13

#endif // AOC2024_DAY13_H
