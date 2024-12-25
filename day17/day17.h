#ifndef AOC2024_DAY17_H
#define AOC2024_DAY17_H

#include <optional>
#include <string>
#include <vector>

namespace day17 {

enum class Opcode {
    Adv = 0,
    Bxl = 1,
    Bst = 2,
    Jnz = 3,
    Bxc = 4,
    Out = 5,
    Bdv = 6,
    Cdv = 7
};

struct ComputerState {
    int instruction_ptr;

    Opcode opcode;
    int operand;

    int register_a;
    int register_b;
    int register_c;
};

class Computer {
  public:
    Computer(long register_a, long register_b, long register_c,
             std::vector<int> program)
        : register_a(register_a), register_b(register_b),
          register_c(register_c), program(std::move(program)) {}

    void execute();
    void execute(long register_a_override);
    void print_output();

    [[nodiscard]] long get_register_a() const { return this->register_a; }
    [[nodiscard]] long get_register_b() const { return this->register_b; }
    [[nodiscard]] long get_register_c() const { return this->register_c; }
    [[nodiscard]] std::vector<ComputerState> get_trace() const {
        return this->trace;
    }
    [[nodiscard]] const std::vector<int> &get_output_buffer() const {
        return this->output_buffer;
    }
    [[nodiscard]] const std::vector<int> &get_program() const {
        return this->program;
    }
    [[nodiscard]] std::optional<Opcode> get_next_opcode() const {
        if (this->instruction_ptr >= this->program.size()) {
            return std::nullopt;
        }

        return static_cast<Opcode>(this->program[this->instruction_ptr]);
    }

  private:
    long register_a;
    long register_b;
    long register_c;

    std::vector<int> output_buffer;

    std::vector<int>::size_type instruction_ptr = 0;
    std::vector<int> program;

    bool skip_next_increment = false;

    std::vector<ComputerState> trace{};

    [[nodiscard]] long get_combo_operand_value(int operand) const;
    [[nodiscard]] long execute_common_div(int operand) const;
    void execute_adv(int operand);
    void execute_bxl(int operand);
    void execute_bst(int operand);
    void execute_jnz(int operand);
    void execute_bxc(int operand);
    void execute_out(int operand);
    void execute_bdv(int operand);
    void execute_cdv(int operand);
};

struct ParsedInput {
    Computer computer;
};

ParsedInput parse_input(std::ifstream &input_stream);

void part1(ParsedInput &input);

long part2(ParsedInput &input);

} // namespace day17

#endif // AOC2024_DAY17_H
