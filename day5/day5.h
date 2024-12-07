//
// Created by jay on 05/12/24.
//

#ifndef AOC2024_DAY5_H
#define AOC2024_DAY5_H

#include <vector>
#include <tuple>
#include <iostream>

namespace day5 {
    struct Update {
        explicit Update(std::vector<int> pages);

        [[nodiscard]] int get_middle() const;

        std::vector<int> pages;
    };

    struct PageRule {
    public:
        PageRule(int before, int after);

        [[nodiscard]] bool validate(const Update &update) const;

        int before;
        int after;
    };

    struct ParsedInput {
        ParsedInput(std::vector<Update> updates, std::vector<PageRule> rules);

        std::vector<Update> updates;
        std::vector<PageRule> rules;
    };

    ParsedInput parse_input(std::istream &input);

    int part1(const ParsedInput &input);

    int part2(const ParsedInput &input);
}

#endif //AOC2024_DAY5_H
