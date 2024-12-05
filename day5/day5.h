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
        Update(std::vector<int> &&pages);

        std::vector<int> pages;
    };

    class PageRule {
        PageRule(int before, int after);

        bool validate(const Update &update);

    private:
        int before;
        int after;
    };

    struct ParsedInput {
        ParsedInput(std::vector<Update> updates, std::vector<PageRule> rules);

        std::vector<Update> updates;
        std::vector<PageRule> rules;
    };

    ParsedInput parse_input(const std::istream &input);
}

#endif //AOC2024_DAY5_H
