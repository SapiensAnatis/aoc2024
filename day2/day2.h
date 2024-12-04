//
// Created by jay on 03/12/24.
//

#ifndef AOC2024_DAY2_H
#define AOC2024_DAY2_H

#include <vector>
#include <fstream>

namespace day2 {
    struct ParsedInput {
        std::vector<std::vector<int>> reports;
    };

    ParsedInput parse_input(std::ifstream &input);

    int part1(const ParsedInput &input);

    int part2(const ParsedInput &input);
}

#endif //AOC2024_DAY2_H
