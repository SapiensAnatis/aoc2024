#include "day21.h"

#include "../lib/aoc.h"
#include "../lib/assert.h"
#include "../lib/grid.h"

#include <iostream>
#include <map>
#include <queue>
#include <regex>

namespace day21 {

ParsedInput parse_input(std::ifstream &input_stream) {
    std::string line;
    std::vector<std::string> codes;

    while (std::getline(input_stream, line)) {
        aoc_assert(line.size() == 4, "Invalid code length");
        codes.push_back(line);
    }

    return {.codes = codes};
}

enum class DpadInput { Up, Activate, Left, Down, Right };

char get_code_char(DpadInput input) {
    switch (input) {
    case DpadInput::Up:
        return '^';
    case DpadInput::Down:
        return 'v';
    case DpadInput::Left:
        return '<';
    case DpadInput::Right:
        return '>';
    case DpadInput::Activate:
        return 'A';
    default:
        return '?';
    }
}

std::ostream &operator<<(std::ostream &stream, DpadInput input) {
    return stream << get_code_char(input);
}

std::ostream &operator<<(std::ostream &stream,
                         const std::vector<DpadInput> &inputs) {
    std::string code_str;
    code_str.reserve(inputs.size());
    for (const auto &input : inputs) {
        code_str += get_code_char(input);
    }

    return stream << code_str;
}

// clang-format off
std::map<char, aoc::Point> digit_positions = {
    {'7', {0, 0}},
    {'8', {1, 0}},
    {'9', {2, 0}},

    {'4', {0, 1}},
    {'5', {1, 1}},
    {'6', {2, 1}},

    {'1', {0, 2}},
    {'2', {1, 2}},
    {'3', {2, 2}},

    {'0', {1, 3}},
    {'A', {2, 3}},
};

std::map<DpadInput, aoc::Point> dpad_positions = {
    {DpadInput::Up,       {1, 0}},
    {DpadInput::Activate, {2, 0}},

    {DpadInput::Left,     {0, 1}},
    {DpadInput::Down,     {1, 1}},
    {DpadInput::Right,    {2, 1}},
};
// clang-format on

std::vector<DpadInput> get_dpad_input_for_code(const std::string &code) {
    aoc::Point cursor_position = digit_positions.at('A');
    std::vector<DpadInput> directions;
    aoc::Point avoid_pos(0, 3);

    for (const auto digit : code) {
        auto digit_pos = digit_positions.at(digit);
        auto vector = digit_pos - cursor_position;

        auto dx_abs = std::abs(vector.dx);
        auto dy_abs = std::abs(vector.dy);
        auto x_move = vector.dx > 0 ? DpadInput::Right : DpadInput::Left;
        auto y_move = vector.dy > 0 ? DpadInput::Down : DpadInput::Up;

        if (digit_pos.x == avoid_pos.x) {
            for (int y = 0; y < dy_abs; y++) {
                directions.push_back(y_move);
            }
            for (int x = 0; x < dx_abs; x++) {
                directions.push_back(x_move);
            }
        } else {
            for (int x = 0; x < dx_abs; x++) {
                directions.push_back(x_move);
            }
            for (int y = 0; y < dy_abs; y++) {
                directions.push_back(y_move);
            }
        }

        directions.push_back(DpadInput::Activate);

        cursor_position = digit_pos;
    }

    return directions;
}

std::vector<DpadInput>
get_dpad_input_for_dpad_inputs(const std::vector<DpadInput> &inputs) {
    aoc::Point cursor_position = dpad_positions.at(DpadInput::Activate);
    std::vector<DpadInput> directions;
    aoc::Point avoid_pos(0, 0);

    for (const auto dpad_input : inputs) {
        auto dpad_pos = dpad_positions.at(dpad_input);
        auto vector = dpad_pos - cursor_position;

        auto dx_abs = std::abs(vector.dx);
        auto dy_abs = std::abs(vector.dy);
        auto x_move = vector.dx > 0 ? DpadInput::Right : DpadInput::Left;
        auto y_move = vector.dy > 0 ? DpadInput::Down : DpadInput::Up;

        if (dpad_pos.x == avoid_pos.x) {
            for (int y = 0; y < dy_abs; y++) {
                directions.push_back(y_move);
            }
            for (int x = 0; x < dx_abs; x++) {
                directions.push_back(x_move);
            }
        } else {
            for (int x = 0; x < dx_abs; x++) {
                directions.push_back(x_move);
            }
            for (int y = 0; y < dy_abs; y++) {
                directions.push_back(y_move);
            }
        }

        directions.push_back(DpadInput::Activate);

        cursor_position = dpad_pos;
    }

    return directions;
}

std::vector<DpadInput> get_final_directions(const std::string &code) {
    auto directions = get_dpad_input_for_code(code);
    std::cout << "Combination for code " << code << ":" << std::endl
              << directions << std::endl;
    auto layer_2_directions = get_dpad_input_for_dpad_inputs(directions);
    std::cout << layer_2_directions << std::endl;
    auto layer_3_directions =
        get_dpad_input_for_dpad_inputs(layer_2_directions);
    std::cout << layer_3_directions << std::endl;

    return layer_3_directions;
}

int get_code_number(const std::string &code) {
    static std::regex num_regex(R"(\d+)");
    auto begin = std::sregex_iterator(code.begin(), code.end(), num_regex);
    aoc_assert(begin != std::sregex_iterator(), "code did not match regex");
    return aoc::parse_int(begin->str(0));
}

long part1(const ParsedInput &input) {
    long complexity = 0;
    for (const auto &code : input.codes) {
        auto directions = get_final_directions(code);
        auto number = get_code_number(code);

        std::cout << "Complexity: " << directions.size() << " * " << number
                  << std::endl
                  << std::endl;
        complexity += static_cast<long>(directions.size()) * number;
    }

    return complexity;
}

} // namespace day21
