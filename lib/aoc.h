//
// Created by jay on 03/12/24.
//

#ifndef AOC2024_AOC_H
#define AOC2024_AOC_H

#include <fstream>
#include <optional>
#include <ranges>
#include <vector>
#include <string_view>

namespace aoc {
    std::ifstream get_example_ifstream();

    std::ifstream get_example_ifstream(int example_num);

    std::ifstream get_real_ifstream();

    std::optional<int> stoi(const std::string_view &input);

    std::vector<std::string_view> split(const std::string &str, char separator);
} // namespace aoc

#endif // AOC2024_AOC_H
