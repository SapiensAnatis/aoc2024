#include "day3.h"

#include <optional>
using namespace day3;

std::optional<MultiplyInstruction> try_parse_instruction(std::istream &input) {
    std::vector<char> buffer;
    buffer.reserve(3);
    input.read(buffer.data(), 3);

    if (input.fail() || input.eof() || buffer.data() != "mul") {
        return std::nullopt;
    }
}

ParsedInput day3::parse_input(std::istream &input) {
    std::vector<MultiplyInstruction> instructions;

    while (!input.fail() && !input.eof()) {
        if (auto instruction = try_parse_instruction(input)) {
            instructions.push_back(*instruction);
        }
    }

    return ParsedInput{instructions};
}

int day3::part1(const ParsedInput &input) { return 0; }
