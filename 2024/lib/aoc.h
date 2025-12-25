//
// Created by jay on 03/12/24.
//

#ifndef AOC2024_AOC_H
#define AOC2024_AOC_H

#include <fstream>
#include <functional>
#include <optional>
#include <sstream>
#include <string_view>
#include <vector>

namespace aoc {

enum Day {
    Day01 = 1,
    Day02 = 2,
    Day03 = 3,
    Day04 = 4,
    Day05 = 5,
    Day06 = 6,
    Day07 = 7,
    Day08 = 8,
    Day09 = 9,
    Day10 = 10,
    Day11 = 11,
    Day12 = 12,
    Day13 = 13,
    Day14 = 14,
    Day15 = 15,
    Day16 = 16,
    Day17 = 17,
    Day18 = 18,
    Day19 = 19,
    Day20 = 20,
    Day21 = 21,
    Day22 = 22,
    Day23 = 23,
    Day24 = 24,
    Day25 = 25,
};

std::ifstream get_example_ifstream(Day day);

std::ifstream get_example_ifstream(Day day, int example_num);

std::ifstream get_real_ifstream(Day day);

int parse_int(const std::string_view &input);

std::optional<int> try_parse_int(const std::string_view &input);

std::optional<long> try_parse_long(const std::string_view &input);

std::optional<long long> try_parse_long_long(const std::string_view &input);

std::optional<int> ctoi(char c);

std::vector<std::string_view> split(const std::string_view &str, char separator);

std::vector<std::string_view> split(const std::string &str, char separator);

template <std::input_or_output_iterator Iterator>
std::string join(char separator, const Iterator &begin, const Iterator &end) {
    std::stringstream ss;
    for (auto it = begin; it != end; ++it) {
        if (it != begin) {
            ss << separator;
        }

        ss << *it;
    }

    return ss.str();
}

void time_execution(const std::string &label, const std::function<void()> &func);

} // namespace aoc

#endif // AOC2024_AOC_H
