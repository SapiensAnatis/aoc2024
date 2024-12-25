#ifndef AOC2024_DAY17_H
#define AOC2024_DAY17_H

#include <queue>
#include <string>

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
    Computer(int register_a, int register_b, int register_c,
             std::vector<int> program)
        : register_a(register_a), register_b(register_b),
          register_c(register_c), program(std::move(program)) {}

    void execute();
    void print_output();

  private:
    int register_a;
    int register_b;
    int register_c;

    std::queue<int> output_buffer;

    int instruction_ptr = 0;
    std::vector<int> program;

    bool skip_next_increment = false;

    std::vector<ComputerState> trace{};

    [[nodiscard]] int get_combo_operand_value(int operand) const;
    [[nodiscard]] int execute_common_div(int operand) const;
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

} // namespace day17

#endif // AOC2024_DAY17_H
