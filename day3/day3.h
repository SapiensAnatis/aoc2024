#ifndef AOC2024_DAY1_H
#define AOC2024_DAY1_H

#include <iostream>
#include <vector>

namespace day3 {
struct ParsedInput {
    std::vector<MultiplyInstruction> instructions;
};

struct MultiplyInstruction {
    int multiplier;
    int multiplicand;
};

day3::ParsedInput parse_input(std::istream &input);

int part1(const day3::ParsedInput &input);
} // namespace day3

#endif // AOC2024_DAY1_H