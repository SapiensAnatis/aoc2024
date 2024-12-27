#include "day21.h"

#include "../lib/aoc.h"
#include "../lib/assert.h"
#include "../lib/grid.h"
#include "../lib/hash.hpp"

#include <iostream>
#include <map>
#include <queue>
#include <regex>

namespace day21 {

enum class DpadInput { Up, Activate, Left, Down, Right };

ParsedInput parse_input(std::ifstream &input_stream) {
    std::string line;
    std::vector<std::string> codes;

    while (std::getline(input_stream, line)) {
        aoc_assert(line.size() == 4, "Invalid code length");
        codes.push_back(line);
    }

    return {.codes = codes};
}

std::map<DpadInput, int> dpad_costs_from_a = {
    {DpadInput::Up, 1},
    {DpadInput::Down, 2},
    {DpadInput::Right, 1},
    {DpadInput::Left, 3},
};

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

std::string get_code_string(const std::vector<DpadInput> &inputs) {
    std::string code_str;
    code_str.reserve(inputs.size());
    for (const auto &input : inputs) {
        code_str += get_code_char(input);
    }

    return code_str;
}

std::ostream &operator<<(std::ostream &stream,
                         const std::vector<DpadInput> &inputs) {
    return stream << get_code_string(inputs);
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

std::vector<DpadInput> get_dpad_input(aoc::Point target_pos,
                                      aoc::Point &cursor_position,
                                      aoc::Point avoid_pos) {

    std::vector<DpadInput> inputs;

    auto vector = target_pos - cursor_position;

    auto dx_abs = std::abs(vector.dx);
    auto dy_abs = std::abs(vector.dy);
    auto x_move = vector.dx > 0 ? DpadInput::Right : DpadInput::Left;
    auto y_move = vector.dy > 0 ? DpadInput::Down : DpadInput::Up;
    auto dx_unit = vector.dx > 0 ? 1 : -1;
    auto dy_unit = vector.dy > 0 ? 1 : -1;

    bool x_first_is_safe =
        cursor_position.y != avoid_pos.y || target_pos.x != avoid_pos.x;
    bool y_first_is_safe =
        cursor_position.x != avoid_pos.x || target_pos.y != avoid_pos.y;

    // I don't really get why this is to be honest
    bool prefer_x_first = x_move == DpadInput::Left;

    aoc_assert(x_first_is_safe || y_first_is_safe, "no safe direction");

    if ((x_first_is_safe && prefer_x_first) || !y_first_is_safe) {
        for (int x = 0; x < dx_abs; x++) {
            inputs.push_back(x_move);
            cursor_position.x += dx_unit;
            aoc_assert(cursor_position != avoid_pos, "illegal cursor move");
        }
        for (int y = 0; y < dy_abs; y++) {
            inputs.push_back(y_move);
            cursor_position.y += dy_unit;
            aoc_assert(cursor_position != avoid_pos, "illegal cursor move");
        }
    } else {
        for (int y = 0; y < dy_abs; y++) {
            inputs.push_back(y_move);
            cursor_position.y += dy_unit;
            aoc_assert(cursor_position != avoid_pos, "illegal cursor move");
        }
        for (int x = 0; x < dx_abs; x++) {
            inputs.push_back(x_move);
            cursor_position.x += dx_unit;
            aoc_assert(cursor_position != avoid_pos, "illegal cursor move");
        }
    }

    inputs.push_back(DpadInput::Activate);

    return inputs;
}

std::vector<DpadInput> get_dpad_input_for_code(const std::string &code) {
    // All the codes end in A, and the last digit of each dpad sequence will be
    // A to trigger a button press. So we do not need to keep track of the robot
    // cursor positions between iterations.
    aoc::Point cursor_position = digit_positions.at('A');
    std::vector<DpadInput> directions;
    aoc::Point avoid_pos(0, 3);

    for (const auto digit : code) {
        auto digit_pos = digit_positions.at(digit);
        auto inputs = get_dpad_input(digit_pos, cursor_position, avoid_pos);
        std::copy(inputs.begin(), inputs.end(), std::back_inserter(directions));
    }

    return directions;
}

std::vector<DpadInput> get_dpad_input_for_dpad_input(
    const std::vector<DpadInput> &previous_layer_inputs) {
    aoc::Point cursor_position = dpad_positions.at(DpadInput::Activate);
    std::vector<DpadInput> directions;
    aoc::Point avoid_pos(0, 0);

    for (const auto dpad_input : previous_layer_inputs) {
        auto dpad_pos = dpad_positions.at(dpad_input);
        auto inputs = get_dpad_input(dpad_pos, cursor_position, avoid_pos);
        std::copy(inputs.begin(), inputs.end(), std::back_inserter(directions));
    }

    return directions;
}

unsigned long get_code_complexity(const std::string &code,
                                  int num_dpad_robots) {
    auto first_directions = get_dpad_input_for_code(code);
    std::cout << "Combination for code " << code << ":" << std::endl
              << first_directions << std::endl;

    std::unordered_map<std::string, unsigned long> complexity_memo;

    std::vector<DpadInput> layer_directions =
        get_dpad_input_for_dpad_input(first_directions);

    std::cout << layer_directions << std::endl;

    std::vector<DpadInput> current_inputs;
    std::vector<DpadInput> final_inputs;

    for (auto input : layer_directions) {
        current_inputs.push_back(input);
        if (input == DpadInput::Activate) {
            std::vector<DpadInput> inputs_to_copy = current_inputs;
            for (int i = 0; i < num_dpad_robots - 1; i++) {
                inputs_to_copy = get_dpad_input_for_dpad_input(inputs_to_copy);
            }

            std::copy(inputs_to_copy.begin(), inputs_to_copy.end(),
                      std::back_inserter(final_inputs));

            current_inputs.clear();
        }
    }

    return final_inputs.size();
}

int get_code_number(const std::string &code) {
    // TODO: can replace with just a substring ignoring the last char
    static std::regex num_regex(R"(\d+)");
    auto begin = std::sregex_iterator(code.begin(), code.end(), num_regex);
    aoc_assert(begin != std::sregex_iterator(), "code did not match regex");
    return aoc::parse_int(begin->str(0));
}

unsigned long puzzle(const ParsedInput &input, int num_dpad_robots) {
    unsigned long total_complexity = 0;
    for (const auto &code : input.codes) {
        auto complexity = get_code_complexity(code, num_dpad_robots);
        auto number = get_code_number(code);

        std::cout << "Complexity: " << complexity << " * " << number
                  << std::endl
                  << std::endl;
        total_complexity += complexity * number;
    }

    return total_complexity;
}

unsigned long part1(const ParsedInput &input) { return puzzle(input, 2); }

} // namespace day21
