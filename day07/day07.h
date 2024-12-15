#ifndef AOC2024_DAY07_H
#define AOC2024_DAY07_H

#include <fstream>
#include <vector>

namespace day7 {

typedef long NodeType;

struct Operation {
    NodeType result;
    std::vector<int> operands;
    bool possible;

    Operation(NodeType result, std::vector<int> operands);
};

struct ParsedInput {
    std::vector<Operation> operations;

    explicit ParsedInput(std::vector<Operation> operations);
};

ParsedInput parse_input(std::ifstream &input_stream);

NodeType part1(const ParsedInput &input);

NodeType part2(const ParsedInput &input);

} // namespace day7

#endif // AOC2024_DAY07_H