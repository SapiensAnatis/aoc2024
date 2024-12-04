#ifndef AOC2024_DAY1_H
#define AOC2024_DAY1_H

#include <iostream>
#include <variant>
#include <vector>

namespace day3 {

struct Instruction {
    std::ptrdiff_t position;

    Instruction(std::ptrdiff_t position) { this->position = position; }
};

struct MultiplyInstruction : Instruction {
    int multiplier;
    int multiplicand;

    MultiplyInstruction(int multiplier, int multiplicand,
                        std::ptrdiff_t position)
        : Instruction(position) {
        this->multiplier = multiplier;
        this->multiplicand = multiplicand;
    }
};

struct EnableDisableInstruction : Instruction {
    bool shouldEnableCounter;

    EnableDisableInstruction(bool shouldEnableCounter, std::ptrdiff_t position)
        : Instruction(position) {
        this->shouldEnableCounter = shouldEnableCounter;
    }
};

typedef std::variant<MultiplyInstruction, EnableDisableInstruction>
    InstructionVariant;

struct ParsedInput {
    std::vector<InstructionVariant> instructions;
};

day3::ParsedInput parse_input(std::istream &input);

int part1(const day3::ParsedInput &input);
} // namespace day3

#endif // AOC2024_DAY1_H