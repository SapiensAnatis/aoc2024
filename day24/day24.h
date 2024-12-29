#ifndef AOC2024_DAY24_H
#define AOC2024_DAY24_H
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace day24 {

enum class LogicGate { AND, OR, XOR };

// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
LogicGate parse_logic_gate(const std::string &value) {
    switch (value) {
    case "AND":
        return LogicGate::AND;
    case "OR":
        return LogicGate::OR;
    case "XOR":
        return LogicGate::XOR;
    default:
        throw std::invalid_argument("Invalid logic gate");
    }
}

struct Wire {
    std::string name;
    bool value;
};

struct WireOperation {
    std::shared_ptr<Wire> wire_1;
    std::shared_ptr<Wire> wire_2;
    std::shared_ptr<Wire> wire_3;
    LogicGate gate;

    WireOperation(std::shared_ptr<Wire> wire_1, std::shared_ptr<Wire> wire_2,
                  std::shared_ptr<Wire> wire_3, LogicGate gate)
        : wire_1(std::move(wire_1)), wire_2(std::move(wire_2)), wire_3(std::move(wire_3)),
          gate(gate) {}
};

struct ParsedInput {
    std::vector<std::shared_ptr<Wire>> wires;
};

ParsedInput parse_input(std::ifstream &input);

unsigned long part1(const ParsedInput &input);

} // namespace day24

#endif // AOC2024_DAY24_H
