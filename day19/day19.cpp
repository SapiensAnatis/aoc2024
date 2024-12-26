#include "day19.h"

#include "../lib/aoc.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <stack>
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

// NOLINTNEXTLINE(misc-no-recursion)
void find_paths_dfs(const std::multimap<int, std::string> &graph,
                    std::vector<std::vector<std::string>> &paths,
                    std::vector<std::string> &&current_path,
                    int current_index) {

    if (current_index == 0) {
        paths.push_back(current_path);
        return;
    }

    auto [begin, end] = graph.equal_range(current_index);
    for (auto it = begin; it != end; ++it) {
        int new_index = current_index - static_cast<int>(it->second.size());
        if (new_index < 0) {
            continue;
        }

        std::vector<std::string> new_path = current_path;
        new_path.push_back(it->second);

        find_paths_dfs(graph, paths, std::move(new_path), new_index);
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
            if (towels.contains(substring)) {
                subpatterns.emplace(i, substring);
            }
        }
    }

    std::vector<std::vector<std::string>> paths;

    for (const auto &[index, _] : subpatterns) {
        if (index == pattern_size) {
            // Valid ending pattern - and thus starting point for DFS
            find_paths_dfs(subpatterns, paths, std::vector<std::string>{},
                           index);
        }
    }

    std::unordered_set<std::string> unique_paths;
    for (const auto &path : paths) {
        std::string path_str;

        for (const auto &path_element : path | std::views::reverse) {
            path_str += path_element;
            path_str += ",";
        }

        unique_paths.insert(path_str);
    }

    return unique_paths;
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
