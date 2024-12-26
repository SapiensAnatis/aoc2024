#include "day19.h"

#include "../lib/aoc.h"
#include "../lib/assert.h"
#include "../lib/hash.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
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

void find_paths_bfs(const std::multimap<int, std::string> &graph,
                    std::unordered_multimap<Node, Node> &parents,
                    const Node &start) {

    std::queue<Node> queue;
    std::unordered_set<Node> explored;
    queue.push(start);

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        auto [begin, end] = graph.equal_range(current.index);
        for (auto it = begin; it != end; it++) {
            auto string = it->second;
            int new_index = current.index - static_cast<int>(string.size());
            Node new_node(new_index, string);

            if (explored.contains(new_node)) {
                continue;
            }

            parents.emplace(new_node, current);
            queue.push(new_node);
            explored.insert(new_node);
        }
    }
}

// NOLINTNEXTLINE(misc-no-recursion)
void analyze_bfs_tree(const std::string &pattern,
                      const std::multimap<int, std::string> &graph,
                      std::unordered_set<std::string> &paths, int current_index,
                      const std::string &path) {

    if (current_index == static_cast<int>(pattern.size())) {
        paths.insert(path);
        return;
    }

    const auto [begin, end] = graph.equal_range(current_index);
    for (auto it = begin; it != end; it++) {
        std::string new_path = path + "," += it->second;
        auto new_index = current_index + static_cast<int>(it->second.size());
        analyze_bfs_tree(pattern, graph, paths, new_index, new_path);
    }
}

std::unordered_set<std::string>
get_compositions(const std::string &pattern,
                 const std::unordered_set<std::string> &towels) {
    std::multimap<int, std::string> subpatterns;

    int pattern_size = static_cast<int>(pattern.size());

    for (int i = 1; i < pattern_size + 1; i++) {
        for (int j = 0; j < i; j++) {
            auto substring = std::string{pattern}.substr(j, i - j);
            int substring_size = static_cast<int>(substring.size());
            if (towels.contains(substring)) {
                subpatterns.emplace(i - substring_size, substring);
            }
        }
    }

    std::unordered_set<std::string> paths;

    for (const auto &[index, substring] : subpatterns) {
        if (index == 0) {
            // Valid starting pattern
            analyze_bfs_tree(pattern, subpatterns, paths,
                             static_cast<int>(substring.size()), substring);
        }
    }

    return paths;
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

int part2(const ParsedInput &input) {
    int permutation_count = 0;

    for (std::vector<std::string>::size_type i = 0; i < input.patterns.size();
         i++) {

        std::cout << "Checking pattern: " << i << "/" << input.patterns.size()
                  << std::endl;

        auto pattern = input.patterns[i];
        auto comps = get_compositions(pattern, input.towels);
        permutation_count += static_cast<int>(comps.size());
    }

    return permutation_count;
}

} // namespace day19
