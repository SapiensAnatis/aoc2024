#ifndef AOC2024_DAY7_H
#define AOC2024_DAY7_H

#include "../lib/aoc.h"

namespace day7 {

struct Operation {
    int result;
    std::vector<int> operands;

    Operation(int result, std::vector<int> operands);
};

struct ParsedInput {
    std::vector<Operation> operations;

    ParsedInput(std::vector<Operation> operations);
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);

} // namespace day7

#endif // AOC2024_DAY7_H