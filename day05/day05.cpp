//
// Created by jay on 05/12/24.
//
#include "day05.h"
#include "../lib/aoc.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <optional>

namespace day5 {

Update::Update(std::vector<int> pages) : pages(std::move(pages)) {}

int Update::get_middle() const {
    assert(this->pages.size() % 2 != 0 &&
           "Update had even number of pages - middle is undefined");

    int index = static_cast<int>(this->pages.size()) / 2;

    assert(index > 0 && index < static_cast<int>(this->pages.size()) &&
           "Middle index bounds check failure");

    return this->pages[index];
}

PageRule::PageRule(int before, int after) : before(before), after(after) {}

bool PageRule::validate(const Update &update) const {
    const auto [before_index, after_index] = get_before_and_after_index(update);

    if (!(before_index && after_index)) {
        return true;
    }

    return before_index < after_index;
}

std::tuple<std::optional<int>, std::optional<int>>
PageRule::get_before_and_after_index(const Update &update) const {
    std::optional<int> before_index;
    std::optional<int> after_index;

    for (auto it = update.pages.begin(); it != update.pages.end(); it++) {
        if (*it == this->before) {
            before_index = it - update.pages.begin();
        } else if (*it == this->after) {
            after_index = it - update.pages.begin();
        }
    }

    return {before_index, after_index};
}

bool PageRule::fix_with_swap(Update &update) const {
    const auto [before_index, after_index] = get_before_and_after_index(update);

    if (!(before_index && after_index)) {
        return false;
    }

    if (before_index < after_index) {
        return false;
    }

    std::iter_swap(update.pages.begin() + *before_index,
                   update.pages.begin() + *after_index);
    return true;
}

ParsedInput::ParsedInput(std::vector<Update> updates,
                         std::vector<PageRule> rules)
    : updates(std::move(updates)), rules(std::move(rules)) {}

ParsedInput parse_input(std::istream &input) {
    std::string line;
    std::vector<PageRule> rules;

    while (std::getline(input, line) && !line.empty()) {
        // A page rule is XX|YY - i.e. always two digits on either side.
        auto line_view = std::string_view(line);
        auto first_page = aoc::try_parse_int(line_view.substr(0, 2));
        auto second_page = aoc::try_parse_int(line_view.substr(3, 2));

        if (!first_page || !second_page) {
            std::cerr << "Failed to parse!\n";
            exit(1);
        }

        rules.emplace_back(*first_page, *second_page);
    }

    std::vector<Update> updates;

    while (std::getline(input, line)) {
        std::vector<int> pages;

        for (auto segment : aoc::split(line, ',')) {
            if (auto parsed_segment = aoc::try_parse_int(segment)) {
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

    for (auto &update : input.updates) {
        bool valid = true;

        for (auto &rule : input.rules) {
            valid &= rule.validate(update);
        }

        if (valid) {
            sum += update.get_middle();
        }
    }

    return sum;
}

int part2(const ParsedInput &input) {
    auto updates_clone = input.updates;
    int fixed_middle_sum = 0;

    for (auto &update : updates_clone) {
        int fixed_count = 0;
        int total_fixed_count = 0;

        do {
            fixed_count = 0;
            for (auto &rule : input.rules) {
                if (rule.fix_with_swap(update)) {
                    fixed_count++;
                    total_fixed_count++;
                }
            }
        } while (fixed_count > 0);

        if (total_fixed_count > 0) {
            fixed_middle_sum += update.get_middle();
        }
    }

    return fixed_middle_sum;
}
} // namespace day5