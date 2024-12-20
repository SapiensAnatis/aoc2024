#include "day07.h"
#include "../lib/aoc.h"
#include "../lib/tree.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

namespace day7 {

Operation::Operation(NodeType result, std::vector<int> operands)
    : result(result), operands(std::move(operands)), possible(false) {}

ParsedInput::ParsedInput(std::vector<Operation> operations)
    : operations(std::move(operations)) {}

ParsedInput parse_input(std::ifstream &input_stream) {
    std::vector<Operation> operations;
    std::string line;

    while (std::getline(input_stream, line)) {
        auto split = aoc::split(line, ':');
        assert(split.size() == 2 && "Malformed line");

        std::optional<NodeType> result = aoc::stol(split[0]);
        assert(result && "Failed to parse result to integer");
        assert(result > 0 && "Result was not positive - potential overflow");

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

    return ParsedInput(operations);
}

NodeType concat(NodeType a, NodeType b) {
    int magnitude = static_cast<int>(std::floor(std::log10(b)));
    auto coeff = static_cast<NodeType>(std::pow(10, magnitude + 1));
    auto result = a * coeff + b;
    return result;
}

// clang-format off
 void write_node_children(Operation &op, int level, /* NOLINT misc-no-recursion */
                        std::shared_ptr<aoc::TreeNode<NodeType>> &&node, bool enable_concat) {
    // clang-format on

    if (level + 1 >= static_cast<int>(op.operands.size())) {
        // Edge of the tree
        if (node->get_value() == op.result) {
            std::cout << "Possible to achieve: " << op.result;
            op.possible = true;

            // std::cout << " via ";
            // std::weak_ptr<aoc::BinaryTreeNode<NodeType>> parent = node;
            // while (true) {
            //     auto parent_lock = parent.lock();
            //     if (!parent_lock) {
            //         break;
            //     }

            //     parent = parent_lock->get_parent();
            //     auto current_lock = parent.lock();
            //     if (!current_lock) {
            //         break;
            //     }

            //     std::cout << " " << current_lock->get_value() << ",";
            // }

            std::cout << std::endl;
        }

        return;
    }

    NodeType next_operand = op.operands[level + 1];

    node->add_child(node->get_value() * next_operand);

    write_node_children(op, level + 1, node->get_child(0), enable_concat);

    if (!op.possible) {
        node->add_child(node->get_value() + next_operand);
        write_node_children(op, level + 1, node->get_child(1), enable_concat);
    }

    if (!op.possible && enable_concat) {
        node->add_child(concat(node->get_value(), next_operand));
        write_node_children(op, level + 1, node->get_child(2), enable_concat);
    }
}

NodeType part1(const ParsedInput &input) {
    NodeType possible_result_sum = 0;

    std::vector<Operation> operations_copy = input.operations;

    for (auto &operation : operations_copy) {
        assert(!operation.operands.empty() && "Operands had no elements");
        aoc::Tree<NodeType> tree(operation.operands[0]);
        write_node_children(operation, 0, tree.get_root(), false);

        if (operation.possible) {
            possible_result_sum += operation.result;
        }
    }

    return possible_result_sum;
}

NodeType part2(const ParsedInput &input) {
    NodeType possible_result_sum = 0;

    std::vector<Operation> operations_copy = input.operations;

    for (auto &operation : operations_copy) {
        assert(!operation.operands.empty() && "Operands had no elements");
        aoc::Tree<NodeType> tree(operation.operands[0]);
        write_node_children(operation, 0, tree.get_root(), true);

        if (operation.possible) {
            possible_result_sum += operation.result;
        }
    }

    return possible_result_sum;
}

} // namespace day7