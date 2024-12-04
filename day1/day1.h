//
// Created by jay on 01/12/24.
//

#ifndef AOC2024_DAY1_H
#define AOC2024_DAY1_H

namespace day1 {
    struct ParsedInput {
        std::vector<int> left;
        std::vector<int> right;
    };

    ParsedInput parse_input(const std::string &path);

    int part1(ParsedInput &input);

    int part2(const ParsedInput &input);
}

#endif //AOC2024_DAY1_H
