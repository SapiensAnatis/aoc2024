#include "day10.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <queue>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>

namespace day10 {

ParsedInput parse_input(std::ifstream &input_stream) {
    return {aoc::parse_grid(input_stream)};
}

int get_score_bfs(const ParsedInput &input, aoc::Point start) {
    int score = 0;

    std::queue<aoc::Point> queue;
    std::unordered_set<aoc::Point> explored;

    queue.push(start);
    explored.insert(start);

    while (!queue.empty()) {
        auto v = queue.front();
        queue.pop();

        assert(input.grid->get_square(v) && "invalid square");
        auto v_value = *input.grid->get_square(v);

        if (v_value == '9') {
            score++;
            explored.insert(v);
        }

        for (auto edge : input.grid->get_adjacent_points(v)) {
            if (explored.contains(edge)) {
                continue;
            }

            assert(input.grid->get_square(edge) && "invalid square");
            if (*input.grid->get_square(edge) - v_value != 1) {
                // Cannot traverse: not increase by 1
                continue;
            }

            explored.insert(edge);
            queue.push(edge);
        }
    }

    return score;
}

int get_score_dfs_part2(const ParsedInput &input, aoc::Point start) {
    int score = 0;

    std::stack<aoc::Point> stack;
    std::unordered_set<aoc::Point> discovered;

    stack.push(start);

    while (!stack.empty()) {
        auto v = stack.top();
        stack.pop();

        assert(input.grid->get_square(v) && "invalid square");
        auto v_value = *input.grid->get_square(v);

        if (v_value == '9') {
            score++;
        }

        for (auto edge : input.grid->get_adjacent_points(v)) {
            assert(input.grid->get_square(edge) && "invalid square");

            if (*input.grid->get_square(edge) - v_value != 1) {
                // Cannot traverse: not increase by 1
                continue;
            }

            stack.push(edge);
        }
    }

    return score;
}

int part1(const ParsedInput &input) {
    std::vector<aoc::Point> trailheads;
    std::unordered_map<aoc::Point, int> scores;

    for (auto it = input.grid->begin(); it != input.grid->end(); it++) {
        if (*it == '0') {
            trailheads.push_back(input.grid->get_point(it));
        }
    }

    for (auto trailhead : trailheads) {
        auto score = get_score_bfs(input, trailhead);
        scores.insert({trailhead, score});
    }

    for (auto pair : scores) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return std::accumulate(
        scores.begin(), scores.end(), 0,
        [](const int acc, const std::pair<aoc::Point, int> &x) {
            return acc + x.second;
        });
}

int part2(const ParsedInput &input) {
    std::vector<aoc::Point> trailheads;
    std::unordered_map<aoc::Point, int> scores;

    for (auto it = input.grid->begin(); it != input.grid->end(); it++) {
        if (*it == '0') {
            trailheads.push_back(input.grid->get_point(it));
        }
    }

    for (auto trailhead : trailheads) {
        auto score = get_score_dfs_part2(input, trailhead);
        scores.insert({trailhead, score});
    }

    for (auto pair : scores) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return std::accumulate(
        scores.begin(), scores.end(), 0,
        [](const int acc, const std::pair<aoc::Point, int> &x) {
            return acc + x.second;
        });
}

} // namespace day10
