//
// Created by jay on 03/12/24.
//

#ifndef AOC2024_DAY02_H
#define AOC2024_DAY02_H

#include <fstream>
#include <vector>

namespace day02 {
struct ParsedInput {
    std::vector<std::vector<int>> reports;
};

ParsedInput parse_input(std::ifstream &input);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);
} // namespace day2

#endif // AOC2024_DAY02_H
