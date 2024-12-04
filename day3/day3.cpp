#include "day3.h"

#include <cassert>
#include <cstring>
#include <optional>
#include <regex>
#include <variant>

using namespace day3;

namespace day3 {

ParsedInput parse_input(std::istream &input) {
    std::string content((std::istreambuf_iterator<char>(input)),
                        (std::istreambuf_iterator<char>()));
    std::vector<InstructionVariant> instructions;

    std::regex multiply_regex(R"(mul\((\d+),(\d+)\))");

    auto content_begin =
        std::sregex_iterator(content.begin(), content.end(), multiply_regex);
    auto content_end = std::sregex_iterator();

    for (std::sregex_iterator match = content_begin; match != content_end;
         match++) {
        auto instruction = *match;
        int multiplier = std::stoi(instruction.str(1));
        int multiplicand = std::stoi(instruction.str(2));

        instructions.push_back(MultiplyInstruction(multiplier, multiplicand,
                                                   instruction.position()));
    }

    std::regex enable_disable_regex(R"((do|don't)\(\))");
    content_begin = std::sregex_iterator(content.begin(), content.end(),
                                         enable_disable_regex);

    for (std::sregex_iterator match = content_begin; match != content_end;
         match++) {
        auto instruction = *match;

        assert((instruction.str() == "do()" ||
                instruction.str() == "don't()")); // Regex fail

        bool shouldEnableCounter = instruction.str() == "do()";

        instructions.push_back(EnableDisableInstruction(
            shouldEnableCounter, instruction.position()));
    }

    return ParsedInput{instructions};
}

struct InstructionVisitor {
    void operator()(EnableDisableInstruction &instruction) {
        this->enabled = instruction.shouldEnableCounter;
    }

    void operator()(MultiplyInstruction &instruction) {
        if (!this->enabled) {
            return;
        }

        this->counter += (instruction.multiplier * instruction.multiplicand);
    }

    int get_result() { return this->counter; }

  private:
    int counter = 0;
    bool enabled = true;
};

int part1(const ParsedInput &input) {
    int result = 0;

    for (auto instruction : input.instructions) {
        if (std::holds_alternative<MultiplyInstruction>(instruction)) {
            MultiplyInstruction multiply_instruction =
                std::get<MultiplyInstruction>(instruction);
            result += multiply_instruction.multiplicand *
                      multiply_instruction.multiplier;
        }
    }

    return result;
}
} // namespace day3