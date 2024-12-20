//
// Created by jay on 01/12/24.
//

#ifndef AOC2024_DAY01_H
#define AOC2024_DAY01_H

#include <string>
#include <vector>

namespace day1 {
struct ParsedInput {
    std::vector<int> left;
    std::vector<int> right;
};

ParsedInput parse_input(const std::string &path);

int part1(ParsedInput &input);

int part2(const ParsedInput &input);
} // namespace day1

#endif // AOC2024_DAY01_H