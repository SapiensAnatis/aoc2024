#include "day24.h"

#include "../lib/assert.h"

#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>

namespace day24 {

ParsedInput parse_input(std::ifstream &input) {
    std::string line;
    std::unordered_map<std::string, std::shared_ptr<Wire>> wires;
    std::vector<WireOperation> wire_operations;

    // Parse initial wire states
    while (std::getline(input, line) && !line.empty()) {
        std::string wire_name = line.substr(0, 3);
        bool wire_value = line[4] == '1';

        wires[wire_name] = std::make_shared<Wire>(wire_name, wire_value);
    }

    static std::regex operation_regex(R"(([a-z0-9]+) (AND|OR|XOR) ([a-z0-9]+) -> ([a-z0-9]+))");

    while (std::getline(input, line)) {
        std::sregex_iterator iter(line.begin(), line.end(), operation_regex);
        aoc_assert(iter != std::sregex_iterator(), "regex did not match");
        aoc_assert(iter->size() == 5, "regex did not have 4 capture groups");

        std::string wire_name_1 = iter->str(1);
        auto [wire_1_it, wire_1_added] = wires.try_emplace(wire_name_1, nullptr);
        if (wire_1_added) {
            wire_1_it->second = std::make_shared<Wire>(wire_name_1, false);
        }

        LogicGate gate = parse_logic_gate(iter->str(2));

        std::string wire_name_2 = iter->str(3);
        auto [wire_2_it, wire_2_added] = wires.try_emplace(wire_name_2, nullptr);
        if (wire_2_added) {
            wire_2_it->second = std::make_shared<Wire>(wire_name_2, false);
        }

        std::string wire_name_3 = iter->str(4);
        auto [wire_3_it, wire_3_added] = wires.try_emplace(wire_name_2, nullptr);
        if (wire_3_added) {
            wire_3_it->second = std::make_shared<Wire>(wire_name_3, false);
        }

        wire_operations.emplace_back(wire_1_it->second, wire_2_it->second, wire_3_it->second, gate);
    }
}

} // namespace day24
