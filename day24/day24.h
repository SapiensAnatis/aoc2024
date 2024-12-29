#ifndef AOC2024_DAY24_H
#define AOC2024_DAY24_H
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace day24 {

enum class LogicGate { AND, OR, XOR };

LogicGate parse_logic_gate(const std::string &value);
std::string print_logic_gate(LogicGate gate);

struct Wire {
    std::string name;
    std::optional<bool> value;
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

    [[nodiscard]] std::string to_string() const;
};

struct ParsedInput {
    std::unordered_map<std::string, std::shared_ptr<Wire>> wires;
    std::vector<WireOperation> wire_operations;
};

ParsedInput parse_input(std::ifstream &input);

unsigned long part1(const ParsedInput &input);

void part2(ParsedInput &input);

} // namespace day24

#endif // AOC2024_DAY24_H
