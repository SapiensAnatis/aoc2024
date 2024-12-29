#include "day24.h"

#include "../lib/assert.h"

#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <ranges>
#include <regex>
#include <string>
#include <unordered_map>

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

std::unordered_map<std::string, std::shared_ptr<Wire>>::iterator
ensure_wire_exists(std::unordered_map<std::string, std::shared_ptr<Wire>> &wires,
                   const std::string &wire_name) {
    auto [it, added] = wires.try_emplace(wire_name, nullptr);
    if (added) {
        it->second = std::make_shared<Wire>(wire_name, std::nullopt);
    }

    return it;
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

    auto wire_view = input.wires | std::ranges::views::values |
                     std::ranges::views::filter([](const std::shared_ptr<Wire> &wire) {
                         return wire->name.starts_with('z');
                     });

    std::vector wires(wire_view.begin(), wire_view.end());
    std::sort(wires.begin(), wires.end(),
              [](const std::shared_ptr<Wire> &wire_1, const std::shared_ptr<Wire> &wire_2) {
                  return wire_1->name < wire_2->name;
              });

    unsigned long result = 0;
    for (std::vector<std::shared_ptr<Wire>>::size_type i = 0; i < wires.size(); i++) {
        auto &wire = wires[i];
        std::cout << wire->name << ": " << *wire->value << std::endl;
        result |= static_cast<unsigned long>(*wire->value) << i;
    }

    return result;
}

} // namespace day24
