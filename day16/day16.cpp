#include "day16.h"
#include "../lib/assert.h"
#include "../lib/grid.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>

namespace day16 {
ParsedInput parse_input(std::ifstream &input_stream) {
    auto grid = aoc::parse_grid(input_stream);
    return {std::move(grid)};
}

std::unordered_map<aoc::Point, int>
get_point_costs_djikstra(const ParsedInput &input, aoc::Point start) {
    std::unordered_map<aoc::Point, int> distances_from_start;
    std::unordered_map<aoc::Point, aoc::Point> previous;
    std::unordered_set<aoc::Point> unvisited;

    distances_from_start.emplace(start, 0);

    for (auto it = input.grid->begin(); it != input.grid->end(); it++) {
        if (*it == '#') {
            continue;
        }

        auto point = input.grid->get_point(it);

        distances_from_start.emplace(point, std::numeric_limits<int>::max());
        unvisited.insert(point);
    }

    auto current_direction = aoc::Vector(1, 0); // east

    while (!unvisited.empty()) {
        if (unvisited.size() % 100 == 0) {
            std::cout << unvisited.size() << std::endl;
        }

        auto current = std::min_element(
            unvisited.begin(), unvisited.end(),
            [&distances_from_start](aoc::Point a, aoc::Point b) {
                return distances_from_start.at(a) < distances_from_start.at(b);
            });

        aoc_assert(current != unvisited.end(),
                   "min_element returned an invalid iterator");

        if (input.grid->get_square_unsafe(*current) == 'E') {
            // We're done
            break;
        }

        auto current_cost = distances_from_start.at(*current);
        auto previous_it = previous.find(*current);
        if (previous_it != previous.end()) {
            current_direction = *current - previous_it->second;
        }

        for (auto adjacent : input.grid->get_adjacent_points(*current)) {
            if (input.grid->get_square_unsafe(adjacent) == '#') {
                continue;
            }

            auto proposed_direction = adjacent - *current;

            aoc_assert(std::abs(proposed_direction.dx) <= 1 &&
                           std::abs(proposed_direction.dy) <= 1,
                       "Invalid direction vector");

            int cost = 1;
            if (proposed_direction != current_direction) {
                cost += 1000;
            }

            int total_cost = current_cost + cost;
            auto cost_it = distances_from_start.find(adjacent);

            if (cost_it->second > total_cost) {
                cost_it->second = total_cost;
                previous[adjacent] = *current;
            }
        }

        unvisited.erase(*current);
    }

    return distances_from_start;
}

std::unordered_map<aoc::Point, aoc::Point>
get_shortest_path_subgraph(const ParsedInput &input, aoc::Point start) {
    std::unordered_map<aoc::Point, int> distances_from_start;
    std::unordered_map<aoc::Point, aoc::Point> previous;
    std::unordered_set<aoc::Point> unvisited;

    distances_from_start.emplace(start, 0);

    for (auto it = input.grid->begin(); it != input.grid->end(); it++) {
        if (*it == '#') {
            continue;
        }

        auto point = input.grid->get_point(it);

        distances_from_start.emplace(point, std::numeric_limits<int>::max());
        unvisited.insert(point);
    }

    auto current_direction = aoc::Vector(1, 0); // east

    while (!unvisited.empty()) {
        auto current = std::min_element(
            unvisited.begin(), unvisited.end(),
            [&distances_from_start](aoc::Point a, aoc::Point b) {
                return distances_from_start.at(a) < distances_from_start.at(b);
            });

        aoc_assert(current != unvisited.end(),
                   "min_element returned an invalid iterator");

        if (input.grid->get_square_unsafe(*current) == 'E') {
            break;
        }

        auto current_cost = distances_from_start.at(*current);
        auto previous_it = previous.find(*current);
        if (previous_it != previous.end()) {
            current_direction = *current - previous_it->second;
        }

        for (auto adjacent : input.grid->get_adjacent_points(*current)) {
            if (input.grid->get_square_unsafe(adjacent) == '#') {
                continue;
            }

            auto proposed_direction = adjacent - *current;

            aoc_assert(std::abs(proposed_direction.dx) <= 1 &&
                           std::abs(proposed_direction.dy) <= 1,
                       "Invalid direction vector");

            int cost = 1;
            if (proposed_direction != current_direction) {
                cost += 1000;
            }

            int total_cost = current_cost + cost;
            auto cost_it = distances_from_start.find(adjacent);

            if (cost_it->second > total_cost) {
                cost_it->second = total_cost;
                previous[adjacent] = *current;
            }
        }

        unvisited.erase(*current);
    }

    return previous;
}

int part1(const ParsedInput &input) {
    auto start_it = std::find(input.grid->begin(), input.grid->end(), 'S');
    aoc_assert(start_it != input.grid->end(), "Failed to find maze start");

    auto start = input.grid->get_point(start_it);

    auto costs = get_point_costs_djikstra(input, start);

    auto end_it = std::find(input.grid->begin(), input.grid->end(), 'E');
    aoc_assert(end_it != input.grid->end(), "Could not find maze end");
    auto end_point = input.grid->get_point(end_it);

    return costs.at(end_point);
}

void print_paths(const ParsedInput &input,
                 const std::unordered_map<aoc::Point, aoc::Point> &subgraph,
                 aoc::Point end) {
    auto new_grid = *input.grid;

    std::stack<aoc::Point> points;
    auto current = end;

    if (subgraph.contains(current)) {
        while (true) {
            points.push(current);
            auto prev_it = subgraph.find(current);
            if (prev_it != subgraph.end()) {
                current = prev_it->second;
            } else {
                break;
            }
        }
    }

    while (!points.empty()) {
        auto p = points.top();
        points.pop();

        new_grid.set_square(p, 'o');
    }

    std::cout << new_grid << std::endl;
}

int part2(const ParsedInput &input) {
    auto start_it = std::find(input.grid->begin(), input.grid->end(), 'S');
    aoc_assert(start_it != input.grid->end(), "Failed to find maze start");

    auto start = input.grid->get_point(start_it);

    auto subgraph = get_shortest_path_subgraph(input, start);

    auto end_it = std::find(input.grid->begin(), input.grid->end(), 'E');
    aoc_assert(end_it != input.grid->end(), "Could not find maze end");
    auto end_point = input.grid->get_point(end_it);

    print_paths(input, subgraph, end_point);

    return 0;
}

} // namespace day16
