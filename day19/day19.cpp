#include "day19.h"

#include "../lib/aoc.h"
#include "../lib/assert.h"
#include "../lib/hash.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <stack>
#include <unordered_map>
#include <unordered_set>

namespace day19 {

ParsedInput parse_input(std::ifstream &input_stream) {
    std::string line;
    std::getline(input_stream, line);

    // Parse available towels
    auto towels_view = std::ranges::views::split(line, ',') |
                       std::ranges::views::transform([](auto &&range) {
                           auto string =
                               std::string(range.begin(), range.end());
                           std::erase(string, ' ');
                           return string;
                       });

    std::unordered_set<std::string> towels{towels_view.begin(),
                                           towels_view.end()};

    // Skip empty line
    std::getline(input_stream, line);

    std::vector<std::string> patterns;

    while (std::getline(input_stream, line)) {
        patterns.push_back(std::move(line));
    }

    return {.towels = towels, .patterns = patterns};
}

bool can_compose(const std::string &pattern,
                 const std::unordered_set<std::string> &towels) {
    auto subpattern_possible = std::vector(pattern.size() + 1, false);
    subpattern_possible[0] = true;

    for (int i = 1; i < static_cast<int>(pattern.size()) + 1; i++) {
        for (int j = 0; j < i; j++) {
            // TODO: can we use a string_view to look up in the set somehow?
            auto substring = std::string{pattern}.substr(j, i - j);
            if (subpattern_possible[j] && towels.contains(substring)) {
                subpattern_possible[i] = true;
                break;
            }
        }
    }

    return subpattern_possible[pattern.size()];
}

std::unordered_set<Node>
analyze_subpatterns_bfs(const std::string &pattern,
                        const std::multimap<int, std::string> &graph) {
    std::queue<Node> queue;
    std::unordered_set<Node> explored;
    std::unordered_set<Node> complete_paths;
    queue.push(Node{0, {}});

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        int path_length =
            std::accumulate(current.path.begin(), current.path.end(), 0,
                            [](int acc, const std::string &segment) {
                                return acc + static_cast<int>(segment.size());
                            });

        if (path_length == static_cast<int>(pattern.size())) {
            complete_paths.insert(current);
            continue;
        }

        auto next_index =
            current.index + static_cast<int>(current.path.empty()
                                                 ? 0
                                                 : current.path.back().size());
        auto [begin, end] = graph.equal_range(next_index);
        for (auto it = begin; it != end; it++) {
            std::vector<std::string> next_path = current.path;
            next_path.push_back(it->second);

            Node next_node(it->first, next_path);

            auto [_, inserted] = explored.insert(next_node);
            if (inserted) {
                queue.push(next_node);
            }
        }
    }

    return complete_paths;
}

int part1(const ParsedInput &input) {
    int possible_count = 0;

    for (const auto &pattern : input.patterns) {
        if (can_compose(pattern, input.towels)) {
            possible_count++;
        }
    }

    return possible_count;
}

// NOLINTNEXTLINE(misc-no-recursion)
long long get_compositions(
    const ParsedInput &input, std::string_view pattern_view,
    std::unordered_map<std::string_view::size_type, long long> &memo) {

    if (pattern_view.empty()) {
        return 1;
    }

    auto memo_it = memo.find(pattern_view.size());
    if (memo_it != memo.end()) {
        return memo_it->second;
    }

    long long compositions = 0;
    for (auto &towel : input.towels) {
        if (towel.size() > pattern_view.size()) {
            continue;
        }

        if (pattern_view.starts_with(towel)) {
            compositions += get_compositions(
                input,
                pattern_view.substr(towel.size(),
                                    pattern_view.size() - towel.size()),
                memo);
        }
    }

    memo[pattern_view.size()] = compositions;

    return compositions;
}

long long part2(const ParsedInput &input) {
    long long permutation_count = 0;

    for (std::vector<std::string>::size_type i = 0; i < input.patterns.size();
         i++) {

        std::cout << "Checking pattern: " << i + 1 << "/"
                  << input.patterns.size() << std::endl;

        auto pattern = input.patterns[i];
        auto memo =
            std::unordered_map<std::string_view::size_type, long long>{};
        auto this_count = get_compositions(input, pattern, memo);

        std::cout << "Pattern " << pattern << " can be made in " << this_count
                  << " ways" << std::endl;

        permutation_count += this_count;
    }

    return permutation_count;
}

} // namespace day19
