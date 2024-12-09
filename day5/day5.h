//
// Created by jay on 05/12/24.
//

#ifndef AOC2024_DAY5_H
#define AOC2024_DAY5_H

#include <iostream>
#include <optional>
#include <tuple>
#include <vector>

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

    bool fix_with_swap(Update &update) const;

    int before;
    int after;

  private:
    std::tuple<std::optional<int>, std::optional<int>>
    get_before_and_after_index(const Update &update) const;
};

struct ParsedInput {
    ParsedInput(std::vector<Update> updates, std::vector<PageRule> rules);

    std::vector<Update> updates;
    std::vector<PageRule> rules;
};

ParsedInput parse_input(std::istream &input);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);
} // namespace day5

#endif // AOC2024_DAY5_H
