#include "day3.h"

#include <algorithm>
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

        // This could probably be made more extensible by not using a regex and
        // parsing manually
        std::regex multiply_regex(R"((mul|don't|do)\((?:(\d+),(\d+))?\))");

        auto content_begin =
                std::sregex_iterator(content.begin(), content.end(), multiply_regex);
        auto content_end = std::sregex_iterator();

        for (std::sregex_iterator match = content_begin; match != content_end;
             match++) {
            const auto &instruction = *match;
            assert(instruction.size() >= 2 &&
                   "Instruction did not have at least one capture group");

            auto instruction_name = instruction.str(1);

            if (instruction_name == "mul") {
                assert(instruction.size() == 4 &&
                       "Multiply instruction did not have three capture groups");

                int multiplier = std::stoi(instruction.str(2));
                int multiplicand = std::stoi(instruction.str(3));

                instructions.emplace_back(MultiplyInstruction(multiplier, multiplicand));
            } else if (instruction_name == "don't") {
                instructions.emplace_back(EnableDisableInstruction(false));
            } else if (instruction_name == "do") {
                instructions.emplace_back(EnableDisableInstruction(true));
            }
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

        [[nodiscard]] int get_result() const { return this->counter; }

    private:
        int counter = 0;
        bool enabled = true;
    };

    int part1(const ParsedInput &input) {
        int result = 0;

        for (auto instruction: input.instructions) {
            if (std::holds_alternative<MultiplyInstruction>(instruction)) {
                MultiplyInstruction multiply_instruction =
                        std::get<MultiplyInstruction>(instruction);
                result += multiply_instruction.multiplicand *
                          multiply_instruction.multiplier;
            }
        }

        return result;
    }

    int part2(const ParsedInput &input) {
        InstructionVisitor visitor = {};

        for (auto instruction: input.instructions) {
            std::visit(visitor, instruction);
        }

        return visitor.get_result();
    }
} // namespace day3