//
// Created by jay on 05/12/24.
//
#include "day5.h"
#include "../lib/aoc.h"
#include <algorithm>
#include <optional>
#include <iostream>
#include <cassert>
#include <map>

namespace day5 {

    Update::Update(std::vector<int> pages) : pages(std::move(pages)) {}

    int Update::get_middle() const {
        assert(this->pages.size() % 2 != 0 && "Update had even number of pages - middle is undefined");

        int index = static_cast<int>(this->pages.size()) / 2;

        assert(index > 0 && index < static_cast<int>(this->pages.size()) && "Middle index bounds check failure");

        return this->pages[index];
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
            bool valid = true;

            for (auto &rule: input.rules) {
                valid &= rule.validate(update);
            }

            if (valid) {
                sum += update.get_middle();
            }
        }

        return sum;
    }


    struct PageWithRules {
        PageWithRules(int page_no, std::vector<int> before, std::vector<int> after) : page_no(page_no),
                                                                                      goes_before(std::move(before)),
                                                                                      goes_after(std::move(after)) {}


        int page_no;
        std::vector<int> goes_before;
        std::vector<int> goes_after;
    };

    int get_position_from_left(int page, const std::map<int, PageWithRules> &pages) { // NOLINT(*-no-recursion)
        static std::map<int, int> previous_left_positions;

        if (previous_left_positions.contains(page)) {
            return previous_left_positions[page];
        }

        const auto &with_rules = pages.at(page);
        int min_pos = 1;

        for (auto preceding_page: with_rules.goes_after) {
            min_pos += get_position_from_left(preceding_page, pages);
        }

        previous_left_positions[page] = min_pos;

        return min_pos;
    }

    int get_position_from_right(int page, const std::map<int, PageWithRules> &pages) { // NOLINT(*-no-recursion)
        static std::map<int, int> previous_right_positions;

        if (previous_right_positions.contains(page)) {
            return previous_right_positions[page];
        }

        PageWithRules with_rules = pages.at(page);
        int min_pos = 1;

        for (auto succeeding_page: with_rules.goes_before) {
            min_pos += get_position_from_right(succeeding_page, pages);
        }

        previous_right_positions[page] = min_pos;

        return min_pos;
    }

    std::map<int, int> get_page_position_map(const ParsedInput &input) {
        std::map<int, PageWithRules> pages;
        std::map<int, int> page_positions;

        for (auto &rule: input.rules) {
            auto pair = pages.try_emplace(rule.before, rule.before, std::vector<int>{}, std::vector<int>{});
            auto it = pair.first;
            it->second.goes_before.push_back(rule.after);

            pair = pages.try_emplace(rule.after, rule.after, std::vector<int>{}, std::vector<int>{});
            it = pair.first;
            it->second.goes_after.push_back(rule.before);
        }


        std::vector<PageWithRules> pages_vec;
        pages_vec.reserve(pages.size());

        for (auto &entry: pages) {
            pages_vec.push_back(entry.second);
        }

        std::sort(pages_vec.begin(), pages_vec.end(), [](const PageWithRules &a, const PageWithRules &b) {
            return a.goes_after.size() < b.goes_after.size();
        });

        for (auto &entry: pages_vec) {
            int position_from_left = get_position_from_left(entry.page_no, pages);
            int position = position_from_left - 0;
            page_positions[entry.page_no] = position;
        }

        return page_positions;
    }


    int part2(const ParsedInput &input) {
        auto position_map = get_page_position_map(input);
        int fixed_sum = 0;

        for (auto &update: input.updates) {
            bool valid = true;

            for (auto &rule: input.rules) {
                valid &= rule.validate(update);

                if (!valid) { break; }
            }

            if (!valid) {
                Update fixed_update = update;

                std::sort(fixed_update.pages.begin(), fixed_update.pages.end(), [&position_map](int a, int b) {
                    return position_map.at(a) < position_map.at(b);
                });

                fixed_sum += fixed_update.get_middle();
            }
        }

        return fixed_sum;
    }
}