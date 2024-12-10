#include "day7.h"
#include "../lib/aoc.h"
#include "../lib/binary_tree.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

namespace day7 {

Operation::Operation(int result, std::vector<int> operands)
    : result(result), operands(std::move(operands)), possible(false) {}

ParsedInput::ParsedInput(std::vector<Operation> operations)
    : operations(std::move(operations)) {}

ParsedInput parse_input(std::ifstream &input_stream) {
    std::vector<Operation> operations;
    std::string line;

    while (std::getline(input_stream, line)) {
        auto split = aoc::split(line, ':');
        assert(split.size() == 2 && "Malformed line");

        std::optional<int> result = aoc::stol(split[0]);
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

// clang-format off
 void write_node_children(Operation &op, int level, /* NOLINT misc-no-recursion */
                        std::shared_ptr<aoc::BinaryTreeNode<long>> &&node) {
    // clang-format on

    if (node->get_value() == op.result) {
        std::cout << "Possible to achieve: " << op.result << "\n";
        op.possible = true;
    }

    if (level + 1 >= static_cast<int>(op.operands.size())) {
        // Edge of the tree
        return;
    }

    long next_operand = op.operands[level + 1];

    node->add_child(node->get_value() * next_operand);
    node->add_child(node->get_value() + next_operand);

    write_node_children(op, level + 1, node->get_first_child());
    write_node_children(op, level + 1, node->get_second_child());
}

long part1(const ParsedInput &input) {
    long possible_result_sum = 0;

    std::vector<Operation> operations_copy = input.operations;

    for (auto &operation : operations_copy) {
        assert(!operation.operands.empty() && "Operands had no elements");
        aoc::BinaryTree<long> tree(operation.operands[0]);
        write_node_children(operation, 0, tree.get_root());

        if (operation.possible) {
            possible_result_sum += operation.result;
        }
    }

    return possible_result_sum;
}

} // namespace day7