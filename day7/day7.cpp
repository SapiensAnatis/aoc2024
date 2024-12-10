#include "day7.h"
#include "../lib/aoc.h"
#include <algorithm>
#include <cassert>

namespace day7 {

Operation::Operation(int result, std::vector<int> operands)
    : result(result), operands(std::move(operands)) {}

ParsedInput::ParsedInput(std::vector<Operation> operations)
    : operations(std::move(operations)) {}

ParsedInput parse_input(std::ifstream &input_stream) {
    std::vector<Operation> operations;
    std::string line;

    while (std::getline(input_stream, line)) {
        auto split = aoc::split(line, ':');
        assert(split.size() == 2 && "Malformed line");

        std::optional<int> result = aoc::stoi(split[0]);
        assert(result && "Failed to parse result to integer");

        std::vector<std::string_view> string_operands =
            aoc::split(split[1], ' ');
        std::vector<int> operands;
        operands.reserve(string_operands.size());

        std::transform(string_operands.begin(), string_operands.end(),
                       std::back_inserter(operands),
                       [](const std::string_view &op) -> int {
                           std::optional<int> parsed = aoc::stoi(op);
                           assert(parsed && "Failed to parse operand!");
                           return *parsed;
                       });

        operations.emplace_back(*result, operands);
    }

    return {operations};
}

} // namespace day7