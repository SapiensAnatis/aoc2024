//
// Created by jay on 05/12/24.
//
#include "day5.h"
#include <algorithm>
#include <optional>

namespace day5 {

    Update::Update(std::vector<int> &&pages) : pages(pages) {}

    PageRule::PageRule(int before, int after) : before(before), after(after) {}

    bool PageRule::validate(const Update &update) {
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


    ParsedInput::ParsedInput(std::vector<Update> updates, std::vector<PageRule> rules) : updates(updates),
                                                                                         rules(rules) {}

    ParsedInput parse_input(const std::istream &input) {

    }
}