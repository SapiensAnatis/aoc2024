#ifndef AOC2024_DAY17_H
#define AOC2024_DAY17_H

#include <optional>
#include <string>
#include <vector>

namespace day17 {

enum class Opcode { Adv = 0, Bxl = 1, Bst = 2, Jnz = 3, Bxc = 4, Out = 5, Bdv = 6, Cdv = 7 };

class Computer {
  public:
    Computer(ulong register_a, ulong register_b, ulong register_c, std::vector<int> program)
        : register_a(register_a), register_b(register_b), register_c(register_c),
          program(std::move(program)) {}

    void execute();
    void execute(ulong register_a_override);
    void print_output();

    [[nodiscard]] const std::vector<int> &get_output_buffer() const { return this->output_buffer; }
    [[nodiscard]] const std::vector<int> &get_program() const { return this->program; }

  private:
    ulong register_a;
    ulong register_b;
    ulong register_c;

    std::vector<int> output_buffer;

    std::vector<int>::size_type instruction_ptr = 0;
    std::vector<int> program;

    bool skip_next_increment = false;

    [[nodiscard]] ulong get_combo_operand_value(int operand) const;
    [[nodiscard]] ulong execute_common_div(int operand) const;
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

ulong part2(ParsedInput &input);

} // namespace day17

#endif // AOC2024_DAY17_H
