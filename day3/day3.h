#ifndef AOC2024_DAY3_H
#define AOC2024_DAY3_H

#include <iostream>
#include <variant>
#include <vector>

namespace day3 {

struct MultiplyInstruction {
    int multiplier;
    int multiplicand;

    MultiplyInstruction(int multiplier, int multiplicand) {
        this->multiplier = multiplier;
        this->multiplicand = multiplicand;
    }
};

struct EnableDisableInstruction {
    bool shouldEnableCounter;

    EnableDisableInstruction(bool shouldEnableCounter) {
        this->shouldEnableCounter = shouldEnableCounter;
    }
};

typedef std::variant<MultiplyInstruction, EnableDisableInstruction>
    InstructionVariant;

struct ParsedInput {
    std::vector<InstructionVariant> instructions;
};

ParsedInput parse_input(std::istream &input);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);
} // namespace day3

#endif // AOC2024_DAY3_H