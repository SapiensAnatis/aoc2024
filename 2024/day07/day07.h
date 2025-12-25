#ifndef AOC2024_DAY07_H
#define AOC2024_DAY07_H

#include <fstream>
#include <vector>

namespace day07 {

typedef long NodeType;

struct Operation {
    NodeType result;
    std::vector<int> operands;
    bool possible;

    Operation(NodeType result, std::vector<int> operands);
};

inline std::ostream &operator<<(std::ostream &os, const Operation &o) {
    os << o.result << ": ";
    for (const auto op : o.operands) {
        os << op << " ";
    }

    return os;
}

struct ParsedInput {
    std::vector<Operation> operations;

    explicit ParsedInput(std::vector<Operation> operations);
};

ParsedInput parse_input(std::ifstream &input_stream);

NodeType part1(const ParsedInput &input);

NodeType part2(const ParsedInput &input);

} // namespace day07

namespace day07::faster {

long part1(const ParsedInput &input);

long part2(const ParsedInput &input);

} // namespace day07::faster

#endif // AOC2024_DAY07_H