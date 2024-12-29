#include "day24.h"

#include "../lib/aoc.h"
#include "../lib/assert.h"
#include "../lib/tree.hpp"

#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <ranges>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace day24 {

LogicGate parse_logic_gate(const std::string &value) {
    if (value == "AND") {
        return LogicGate::AND;
    }
    if (value == "OR") {
        return LogicGate::OR;
    }
    if (value == "XOR") {
        return LogicGate::XOR;
    }

    throw std::invalid_argument("Invalid logic gate");
}

std::string print_logic_gate(LogicGate gate) {
    switch (gate) {
    case LogicGate::AND:
        return "AND";
    case LogicGate::OR:
        return "OR";
    case LogicGate::XOR:
        return "XOR";
    default:
        throw std::invalid_argument("Invalid logic gate");
    }
}

std::unordered_map<std::string, std::shared_ptr<Wire>>::iterator
ensure_wire_exists(std::unordered_map<std::string, std::shared_ptr<Wire>> &wires,
                   const std::string &wire_name) {
    auto [it, added] = wires.try_emplace(wire_name, nullptr);
    if (added) {
        it->second = std::make_shared<Wire>(wire_name, std::nullopt);
    }

    return it;
}

std::string WireOperation::to_string() const {
    std::stringstream ss;

    ss << this->wire_1->name << " ";
    ss << print_logic_gate(this->gate) << " ";
    ss << this->wire_2->name << " ";
    ss << "-> ";
    ss << this->wire_3->name;

    return ss.str();
}

ParsedInput parse_input(std::ifstream &input) {
    std::string line;
    std::unordered_map<std::string, std::shared_ptr<Wire>> wires;
    std::vector<WireOperation> wire_operations;

    while (std::getline(input, line) && !line.empty()) {
        std::string wire_name = line.substr(0, 3);
        aoc_assert(line[5] == '1' || line[5] == '0', "failed to get wire initial state");
        bool wire_value = line[5] == '1';

        wires[wire_name] = std::make_shared<Wire>(wire_name, wire_value);
    }

    static std::regex operation_regex(R"(([a-z0-9]+) (AND|OR|XOR) ([a-z0-9]+) -> ([a-z0-9]+))");

    while (std::getline(input, line)) {
        std::sregex_iterator iter(line.begin(), line.end(), operation_regex);
        aoc_assert(iter != std::sregex_iterator(), "regex did not match");
        aoc_assert(iter->size() == 5, "regex did not have 4 capture groups");

        std::string wire_name_1 = iter->str(1);
        auto wire_1_it = ensure_wire_exists(wires, wire_name_1);

        LogicGate gate = parse_logic_gate(iter->str(2));

        std::string wire_name_2 = iter->str(3);
        auto wire_2_it = ensure_wire_exists(wires, wire_name_2);

        std::string wire_name_3 = iter->str(4);
        auto wire_3_it = ensure_wire_exists(wires, wire_name_3);

        wire_operations.emplace_back(wire_1_it->second, wire_2_it->second, wire_3_it->second, gate);
    }

    return {.wires = wires, .wire_operations = wire_operations};
}
unsigned long part1(const ParsedInput &input) {
    bool all_z_wires_have_value = false;

    while (!all_z_wires_have_value) {
        for (const auto &operation : input.wire_operations) {
            if (!operation.wire_1->value || !operation.wire_2->value) {
                continue;
            }

            bool result;

            switch (operation.gate) {
            case LogicGate::AND: {
                result = static_cast<int>(*operation.wire_1->value) &
                         static_cast<int>(*operation.wire_2->value);
                break;
            }
            case LogicGate::OR: {
                result = static_cast<int>(*operation.wire_1->value) |
                         static_cast<int>(*operation.wire_2->value);
                break;
            }
            case LogicGate::XOR: {
                result = static_cast<int>(*operation.wire_1->value) ^
                         static_cast<int>(*operation.wire_2->value);
                break;
            }
            default: {
                throw std::runtime_error("Unsupported gate");
            }
            }

            operation.wire_3->value = result;
        }

        all_z_wires_have_value = std::ranges::none_of(input.wires, [](const auto &p) {
            auto &wire = p.second;
            return wire->name.starts_with('z') && !wire->value.has_value();
        });
    }

    auto z_wire_view =
        input.wires | std::ranges::views::values |
        std::ranges::views::filter([](const auto &x) { return x->name.starts_with('z'); });

    std::vector wires(z_wire_view.begin(), z_wire_view.end());
    std::ranges::sort(wires, [](const auto &a, const auto &b) { return a->name < b->name; });

    unsigned long result = 0;
    for (std::vector<std::shared_ptr<Wire>>::size_type i = 0; i < wires.size(); i++) {
        auto &wire = wires[i];
        std::cout << wire->name << ": " << *wire->value << std::endl;
        result |= static_cast<unsigned long>(*wire->value) << i;
    }

    return result;
}

// NOLINTNEXTLINE(misc-no-recursion)
void walk_tree(const WireOperation &operation,
               const std::unordered_map<std::string, WireOperation> &operations_by_output_wire,
               std::stack<WireOperation> &op_stack) {
    op_stack.push(operation);

    auto parent_1 = operations_by_output_wire.find(operation.wire_1->name);
    if (parent_1 != operations_by_output_wire.end()) {
        auto op = parent_1->second;
        walk_tree(op, operations_by_output_wire, op_stack);
    }

    auto parent_2 = operations_by_output_wire.find(operation.wire_2->name);
    if (parent_2 != operations_by_output_wire.end()) {
        auto op = parent_2->second;
        walk_tree(op, operations_by_output_wire, op_stack);
    }
}

void rename_carry(std::vector<WireOperation> &wire_operations_in_order) {
    for (const auto &operation : wire_operations_in_order) {
        std::string operand_1 = std::min(operation.wire_1->name, operation.wire_2->name);
        std::string operand_2 = std::max(operation.wire_1->name, operation.wire_2->name);

        if (operand_1.starts_with("CARRY") && operand_2.starts_with("XOR") &&
            operation.gate == LogicGate::AND) {
            auto number_1 = operand_1.substr(5, 2);
            auto number_2 = operand_2.substr(3, 2);
            aoc_assert(aoc::parse_int(number_1) == aoc::parse_int(number_2) - 1, "inconsistent N");
            operation.wire_3->name = "CARRY_INTERMEDIATE" + number_2;
        }

        if (operand_1.starts_with("AND") && operand_2.starts_with("CARRY_INTERMEDIATE") &&
            operation.gate == LogicGate::OR) {
            auto number_1 = operand_1.substr(3, 2);
            auto number_2 = operand_2.substr(18, 2);
            aoc_assert(aoc::parse_int(number_1) == aoc::parse_int(number_2), "inconsistent N");

            operation.wire_3->name = "CARRY" + number_1;
        }
    }
}

void swap_output_wires(std::vector<WireOperation> &wire_ops, const std::string &wire_1_name,
                       const std::string &wire_2_name) {
    auto op_1_it =
        std::ranges::find_if(wire_ops.begin(), wire_ops.end(), [&wire_1_name](const auto &op) {
            return op.wire_3->name == wire_1_name;
        });
    aoc_assert(op_1_it != wire_ops.end(), "could not find wire_1");

    auto op_2_it =
        std::ranges::find_if(wire_ops.begin(), wire_ops.end(), [&wire_2_name](const auto &op) {
            return op.wire_3->name == wire_2_name;
        });
    aoc_assert(op_2_it != wire_ops.end(), "could not find wire_2");

    std::swap(op_1_it->wire_3, op_2_it->wire_3);
}

void part2(ParsedInput &input) {
    std::unordered_map<std::string, aoc::Tree<WireOperation>> operation_trees;
    std::unordered_map<std::string, WireOperation> operations_by_output_wire;

    for (const auto &operation : input.wire_operations) {
        aoc_assert(!operations_by_output_wire.contains(operation.wire_3->name),
                   "output wire was not unique");

        operations_by_output_wire.emplace(operation.wire_3->name, operation);
    }

    auto z_wire_view = input.wire_operations | std::ranges::views::filter([](const auto &x) {
                           return x.wire_3->name.starts_with('z');
                       });

    std::vector z_wire_vec(z_wire_view.begin(), z_wire_view.end());

    std::ranges::sort(z_wire_vec, [](const WireOperation &a, const WireOperation &b) {
        return a.wire_3->name < b.wire_3->name;
    });

    std::vector<WireOperation> wire_operations_in_order;
    std::unordered_set<std::string> already_added;

    for (const auto &operation : z_wire_vec) {
        std::stack<WireOperation> op_stack;

        walk_tree(operation, operations_by_output_wire, op_stack);

        while (!op_stack.empty()) {
            auto op = op_stack.top();
            auto op_string = op.to_string();

            op_stack.pop();

            if (already_added.contains(op_string)) {
                continue;
            }

            wire_operations_in_order.push_back(op);
            already_added.insert(op_string);
        }
    }

    /*
     * Stolen from:
     * https://old.reddit.com/r/adventofcode/comments/1hnb969/2024_day_24_part_2_aliasing_wires_to_spot_the/
     *
     * When the rename starts to fail, swap the wires and then run the program again
     * For example, the rename failed at these for not being XOR(N) xor CARRY(N-1) -> Z(N)
     * - XOR12 XOR CARRY11 -> qdg, so I swapped z12 and qdg
     * - CARRY18 XOR XOR19 -> vvf, so I swapped z19 and vvf
     *
     * The third one was tricky and was a wrong operand being AND(N) XOR CARRY(N-1) -> Z(N)
     * - AND23 XOR CARRY22 -> z23
     *   fgn XOR shg -> z23
     *
     *   y23 AND x23 -> fgn
     *   x23 XOR y23 -> dck
     *
     * We want XOR23 XOR CARRY22 -> z23 there so swap AND23 (fgn) and XOR23 (dck)
     *
     * Then there was one more violation of XOR(N) xor CARRY(N-1) -> Z(N)
     * - XOR37 XOR CARRY36 -> nvh, so I swapped z37 and nvh
     *
     * This is not generic to any input but that sounds really hard to do and I already got my star
     * (even if it was a hollow victory)
     */

    swap_output_wires(wire_operations_in_order, "z12", "qdg");
    swap_output_wires(wire_operations_in_order, "z19", "vvf");
    swap_output_wires(wire_operations_in_order, "fgn", "dck");
    swap_output_wires(wire_operations_in_order, "z37", "nvh");

    // Rename AND/XOR registers pass
    for (const auto &operation : wire_operations_in_order) {
        std::string operand_1 = std::min(operation.wire_1->name, operation.wire_2->name);
        std::string operand_2 = std::max(operation.wire_1->name, operation.wire_2->name);

        if (operand_1.starts_with('x') && operand_2.starts_with('y')) {
            auto number = operand_1.substr(1, 2);
            operation.wire_3->name = print_logic_gate(operation.gate) + number;
        }
    }

    // Rename AND00->CARRY00
    auto and_00_it = std::ranges::find_if(wire_operations_in_order, [](const WireOperation &op) {
        return op.wire_3->name == "AND00";
    });
    aoc_assert(and_00_it != wire_operations_in_order.end(), "failed to get AND00");
    and_00_it->wire_3->name = "CARRY00";

    rename_carry(wire_operations_in_order);

    for (const auto &operation : wire_operations_in_order) {
        std::cout << operation.to_string() << std::endl;
    }
}

} // namespace day24
