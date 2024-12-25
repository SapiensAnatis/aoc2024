#include "day17.h"
#include "../lib/aoc.h"
#include "../lib/assert.h"

#include <cmath>
#include <format>
#include <fstream>
#include <iostream>
#include <regex>

namespace day17 {

void Computer::execute() {
    this->instruction_ptr = 0;
    this->skip_next_increment = false;
    this->output_buffer.clear();
    this->trace.clear();

    while (this->instruction_ptr + 1 < this->program.size()) {
        auto opcode = static_cast<Opcode>(this->program[instruction_ptr]);
        auto operand = this->program[instruction_ptr + 1];

        this->trace.emplace_back(this->instruction_ptr, opcode, operand,
                                 this->register_a, this->register_b,
                                 this->register_c);

        switch (opcode) {
        case Opcode::Adv:
            this->execute_adv(operand);
            break;
        case Opcode::Bxl:
            this->execute_bxl(operand);
            break;
        case Opcode::Bst:
            this->execute_bst(operand);
            break;
        case Opcode::Jnz:
            this->execute_jnz(operand);
            break;
        case Opcode::Bxc:
            this->execute_bxc(operand);
            break;
        case Opcode::Out:
            this->execute_out(operand);
            break;
        case Opcode::Bdv:
            this->execute_bdv(operand);
            break;
        case Opcode::Cdv:
            this->execute_cdv(operand);
            break;
        default:
            throw std::out_of_range("Invalid opcode");
        }

        if (!this->skip_next_increment) {
            this->instruction_ptr += 2;
        }

        this->skip_next_increment = false;
    }
}

void Computer::execute(long register_a_override) {
    this->register_a = register_a_override;
    this->execute();
}

void Computer::print_output() {
    for (std::vector<int>::size_type i = 0; i < this->output_buffer.size();
         i++) {
        auto num = this->output_buffer[i];
        std::cout << num;

        if (i != this->output_buffer.size() - 1) {
            std::cout << ",";
        }
    }

    std::cout << std::endl;
}

long Computer::get_combo_operand_value(int operand) const {
    switch (operand) {
    case 0:
    case 1:
    case 2:
    case 3:
        return operand;
    case 4:
        return this->register_a;
    case 5:
        return this->register_b;
    case 6:
        return this->register_c;
    default:
        throw std::out_of_range("Operand out of range!");
    }
}

long Computer::execute_common_div(int operand) const {
    long numerator = this->register_a;
    long double denominator =
        std::pow(2, this->get_combo_operand_value(operand));

    long double result = numerator / denominator;
    long double result_trunc = std::trunc(result);

    return static_cast<long>(result_trunc);
}

void Computer::execute_adv(int operand) {
    this->register_a = execute_common_div(operand);
}

void Computer::execute_bxl(int operand) {
    long result = this->register_b ^ operand;
    this->register_b = result;
}

void Computer::execute_bst(int operand) {
    long result = this->get_combo_operand_value(operand) % 8;
    this->register_b = result;
}

void Computer::execute_jnz(int operand) {
    if (this->register_a != 0) {
        this->instruction_ptr = operand;
        this->skip_next_increment = true;
    }
}

void Computer::execute_bxc([[maybe_unused]] int operand) {
    long result = this->register_b ^ this->register_c;
    this->register_b = result;
}

void Computer::execute_out(int operand) {
    long result = this->get_combo_operand_value(operand) % 8;
    aoc_assert(result < std::numeric_limits<int>::max(),
               "Overflow detected on out instruction");
    this->output_buffer.push_back(static_cast<int>(result));
}

void Computer::execute_bdv(int operand) {
    this->register_b = execute_common_div(operand);
}

void Computer::execute_cdv(int operand) {
    this->register_c = execute_common_div(operand);
}

int parse_register_line(const std::string &register_line) {
    static std::regex register_regex(R"(Register \w: (\d+))");

    auto match_start = std::sregex_iterator(
        register_line.begin(), register_line.end(), register_regex);
    auto match_end = std::sregex_iterator();

    aoc_assert(match_start != match_end, "Regex did not match");

    aoc_assert(match_start->size() == 2, "Match did not have a capture group");
    auto value = match_start->str(1);

    return std::stoi(value);
}

std::vector<int> parse_program_line(const std::string &program_line) {
    static std::regex program_regex(R"(Program: (\d+,.*))");

    auto match_start = std::sregex_iterator(program_line.begin(),
                                            program_line.end(), program_regex);
    auto match_end = std::sregex_iterator();

    aoc_assert(match_start != match_end, "Regex did not match");

    aoc_assert(match_start->size() == 2, "Match did not have a capture group");
    auto program_string = match_start->str(1);

    auto instructions = aoc::split(program_string, ',');
    auto parsed_instructions = std::vector<int>(instructions.size(), 0);

    std::transform(instructions.begin(), instructions.end(),
                   parsed_instructions.begin(),
                   [](auto ins) { return *aoc::stoi(ins); });

    return parsed_instructions;
}

ParsedInput parse_input(std::ifstream &input_stream) {
    std::string register_line;
    std::string empty_line;
    std::string program_line;

    // Register A
    std::getline(input_stream, register_line);
    int register_a = parse_register_line(register_line);
    // Register B
    std::getline(input_stream, register_line);
    int register_b = parse_register_line(register_line);
    // Register C
    std::getline(input_stream, register_line);
    int register_c = parse_register_line(register_line);

    // Skip a line
    std::getline(input_stream, empty_line);

    // Program line
    std::getline(input_stream, program_line);
    auto program = parse_program_line(program_line);

    return {Computer(register_a, register_b, register_c, program)};
}

void part1(ParsedInput &input) {
    input.computer.execute();
    input.computer.print_output();
}

long part2(ParsedInput &input) {
    auto program = input.computer.get_program();

    long test_value = 0b0000000000000000000000000000000000000000000000;
    int target_program_digit = static_cast<int>(program.size()) - 1;

    int iterations = 0;

    while (iterations < 20) {
        iterations++;

        std::cout << "Looking for digit " << program[target_program_digit]
                  << std::endl;

        int i = 0;
        for (; i < 8; i++) {
            long new_test_value = test_value | i;
            std::cout << "Trying offset " << i << std::endl;
            std::cout << "Executing with register_a = "
                      << std::format("{:b}", new_test_value) << std::endl;
            input.computer.execute(new_test_value);
            input.computer.print_output();

            auto &output = input.computer.get_output_buffer();

            // Modifying the last 3 bits of register A modifies the first digit
            // of the output
            if (output[0] == program[target_program_digit]) {
                std::cout << "Found valid shift" << std::endl << std::endl;
                break;
            }
        }

        if (i == 8) {
            throw std::logic_error("failed to find valid shift");
        }

        test_value |= i;
        test_value = test_value << 3;
        target_program_digit--;
    }

    return 0;
}

} // namespace day17
