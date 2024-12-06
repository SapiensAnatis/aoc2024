//
// Created by jay on 05/12/24.
//
#include "day5.h"
#include "../lib/aoc.h"
#include <algorithm>
#include <optional>
#include <iostream>

namespace day5 {

    Update::Update(std::vector<int> pages) : pages(std::move(pages)) {}

    int Update::get_middle() const {
        if (this->pages.size() % 2 == 0) {
            std::cerr << "Middle is undefined\n";
            return 0;
        }

        return (static_cast<int>(this->pages.size()) / 2) + 1;
    }

    PageRule::PageRule(int before, int after) : before(before), after(after) {}

    bool PageRule::validate(const Update &update) const {
        std::optional<int> before_index;
        std::optional<int> after_index;

        for (auto it = update.pages.begin(); it != update.pages.end(); it++) {
            if (*it == this->before) {
                before_index = it - update.pages.begin();
            } else if (*it == this->after) {
                after_index = it - update.pages.begin();
            }
        }

        if (!(before_index && after_index)) {
            return true;
        }

        return before_index < after_index;
    }


    ParsedInput::ParsedInput(std::vector<Update> updates, std::vector<PageRule> rules) : updates(std::move(updates)),
                                                                                         rules(std::move(rules)) {}

    ParsedInput parse_input(std::istream &input) {
        std::string line;
        std::vector<PageRule> rules;

        while (std::getline(input, line) && !line.empty()) {
            // A page rule is XX|YY - i.e. always two digits on either side.
            auto line_view = std::string_view(line);
            auto first_page = aoc::stoi(line_view.substr(0, 2));
            auto second_page = aoc::stoi(line_view.substr(3, 2));

            if (!first_page || !second_page) {
                std::cerr << "Failed to parse!\n";
                exit(1);
            }

            rules.emplace_back(*first_page, *second_page);
        }

        std::vector<Update> updates;

        while (std::getline(input, line)) {
            std::vector<int> pages;

            for (auto segment: aoc::split(line, ',')) {
                if (auto parsed_segment = aoc::stoi(segment)) {
                    pages.push_back(*parsed_segment);
                } else {
                    std::cerr << "Parse failure\n";
                    exit(1);
                }
            }

            updates.emplace_back(pages);
        }

        return {updates, rules};
    }

    int part1(const ParsedInput &input) {
        int sum = 0;

        for (auto &update: input.updates) {
            for (auto &rule: input.rules) {
                if (rule.validate(update)) {
                    sum += update.get_middle();
                }
            }
        }

        return sum;
    }
}