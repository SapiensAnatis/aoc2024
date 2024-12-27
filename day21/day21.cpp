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

struct Move {
    DpadInput from;
    DpadInput to;
    int robot_num;
};

bool operator==(const Move &lhs, const Move &rhs) {
    return lhs.from == rhs.from && lhs.to == rhs.to &&
           lhs.robot_num == rhs.robot_num;
}

} // namespace day21

template <> struct std::hash<day21::Move> {
    size_t operator()(const day21::Move &a) const noexcept {
        size_t seed = 0;
        aoc::hash_combine(seed, a.from);
        aoc::hash_combine(seed, a.to);
        aoc::hash_combine(seed, a.robot_num);
        return seed;
    }
};

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

std::vector<DpadInput> get_dpad_input(aoc::Point from, aoc::Point to,
                                      aoc::Point avoid_pos) {

    std::vector<DpadInput> inputs;

    auto vector = to - from;

    auto dx_abs = std::abs(vector.dx);
    auto dy_abs = std::abs(vector.dy);
    auto x_move = vector.dx > 0 ? DpadInput::Right : DpadInput::Left;
    auto y_move = vector.dy > 0 ? DpadInput::Down : DpadInput::Up;
    auto dx_unit = vector.dx > 0 ? 1 : -1;
    auto dy_unit = vector.dy > 0 ? 1 : -1;

    bool x_first_is_safe = from.y != avoid_pos.y || to.x != avoid_pos.x;
    bool y_first_is_safe = from.x != avoid_pos.x || to.y != avoid_pos.y;

    // I don't really get why this is to be honest
    bool prefer_x_first = x_move == DpadInput::Left;

    aoc_assert(x_first_is_safe || y_first_is_safe, "no safe direction");

    if ((x_first_is_safe && prefer_x_first) || !y_first_is_safe) {
        for (int x = 0; x < dx_abs; x++) {
            inputs.push_back(x_move);
            from.x += dx_unit;
            aoc_assert(from != avoid_pos, "illegal cursor move");
        }
        for (int y = 0; y < dy_abs; y++) {
            inputs.push_back(y_move);
            from.y += dy_unit;
            aoc_assert(from != avoid_pos, "illegal cursor move");
        }
    } else {
        for (int y = 0; y < dy_abs; y++) {
            inputs.push_back(y_move);
            from.y += dy_unit;
            aoc_assert(from != avoid_pos, "illegal cursor move");
        }
        for (int x = 0; x < dx_abs; x++) {
            inputs.push_back(x_move);
            from.x += dx_unit;
            aoc_assert(from != avoid_pos, "illegal cursor move");
        }
    }

    inputs.push_back(DpadInput::Activate);

    return inputs;
}

unsigned long
// NOLINTNEXTLINE(misc-no-recursion)
get_pair_complexity(DpadInput from, DpadInput to, int robot_num,
                    std::unordered_map<Move, unsigned long> &cache) {
    Move move(from, to, robot_num);
    auto cache_it = cache.find(move);
    if (cache_it != cache.end()) {
        return cache_it->second;
    }

    auto from_pos = dpad_positions.at(from);
    auto to_pos = dpad_positions.at(to);
    aoc::Point avoid(0, 0);

    auto moves = get_dpad_input(from_pos, to_pos, avoid);
    unsigned long complexity = 0;

    for (std::vector<DpadInput>::size_type i = 0; i < moves.size(); i++) {
        auto current = moves[i];
        auto previous = i == 0 ? DpadInput::Activate : moves[i - 1];

        if (robot_num == 1) {
            // This is the final robot a.k.a. us
            complexity += 1;
        } else {
            complexity +=
                get_pair_complexity(previous, current, robot_num - 1, cache);
        }
    }

    cache[move] = complexity;
    return complexity;
}

std::vector<DpadInput> get_dpad_input_for_code(const std::string &code) {
    aoc::Point cursor_position = digit_positions.at('A');
    std::vector<DpadInput> directions;
    aoc::Point avoid_pos(0, 3);

    for (const auto digit : code) {
        auto digit_pos = digit_positions.at(digit);
        auto inputs = get_dpad_input(cursor_position, digit_pos, avoid_pos);
        std::copy(inputs.begin(), inputs.end(), std::back_inserter(directions));

        cursor_position = digit_pos;
    }

    return directions;
}

unsigned long
get_code_complexity(const std::string &code,
                    std::unordered_map<Move, unsigned long> &complexity_memo,
                    int num_dpad_robots) {
    auto first_directions = get_dpad_input_for_code(code);
    std::cout << "Combination for code " << code << ":" << std::endl
              << first_directions << std::endl;

    std::vector<DpadInput> current_inputs;
    unsigned long total_complexity = 0;

    for (std::vector<DpadInput>::size_type i = 0; i < first_directions.size();
         i++) {
        auto current = first_directions[i];
        auto previous = i == 0 ? DpadInput::Activate : first_directions[i - 1];

        total_complexity += get_pair_complexity(
            previous, current, num_dpad_robots, complexity_memo);
    }

    return total_complexity;
}

int get_code_number(const std::string &code) {
    // The code is always numeric until the last digit
    std::string_view numeric_part(code.begin(), code.end() - 1);
    return aoc::parse_int(numeric_part);
}

unsigned long puzzle(const ParsedInput &input, int num_dpad_robots) {
    unsigned long total_complexity = 0;
    std::unordered_map<Move, unsigned long> complexity_memo;

    for (const auto &code : input.codes) {
        auto complexity =
            get_code_complexity(code, complexity_memo, num_dpad_robots);
        auto number = get_code_number(code);

        std::cout << "Complexity: " << complexity << " * " << number
                  << std::endl
                  << std::endl;
        total_complexity += complexity * number;
    }

    return total_complexity;
}

unsigned long part1(const ParsedInput &input) { return puzzle(input, 2); }

unsigned long part2(const ParsedInput &input) { return puzzle(input, 25); }

} // namespace day21
