#include "day16.h"
#include "../lib/assert.h"
#include "../lib/grid.h"
#include "../lib/hash.hpp"
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

bool operator==(const PointWithDirection &a, const PointWithDirection &b) {
    return a.point == b.point && a.direction == b.direction;
}

const std::array<aoc::Vector, 4> directions = {
    aoc::Vector(aoc::Direction::North),
    aoc::Vector(aoc::Direction::East),
    aoc::Vector(aoc::Direction::South),
    aoc::Vector(aoc::Direction::West),
};

// CHEATED: I was trying to find multiple paths without taking into account
// the direction you were approaching each point from. So it would only ever
// find one shortest path and I couldn't do part 2. Needed to see other
// solutions that incorporated the direction as a key in the set/dict
std::unordered_multimap<PointWithDirection, PointWithDirection>
get_shortest_path_subgraph(const ParsedInput &input, aoc::Point start) {
    std::unordered_map<PointWithDirection, int> distances_from_start;
    std::unordered_multimap<PointWithDirection, PointWithDirection> previous;
    std::unordered_set<PointWithDirection> unvisited;

    distances_from_start.emplace(
        PointWithDirection(start, aoc::Vector(aoc::Direction::East)), 0);

    for (auto it = input.grid->begin(); it != input.grid->end(); it++) {
        if (*it == '#') {
            continue;
        }

        auto point = input.grid->get_point(it);

        for (const auto dir : directions) {
            PointWithDirection pwd(point, dir);

            distances_from_start.emplace(pwd, std::numeric_limits<int>::max());
            unvisited.insert(pwd);
        }
    }

    while (!unvisited.empty()) {
        auto current = std::min_element(
            unvisited.begin(), unvisited.end(),
            [&distances_from_start](PointWithDirection a,
                                    PointWithDirection b) {
                return distances_from_start.at(a) < distances_from_start.at(b);
            });

        aoc_assert(current != unvisited.end(),
                   "min_element returned an invalid iterator");

        if (input.grid->get_square_unsafe(current->point) == 'E') {
            break;
        }

        auto current_cost = distances_from_start.at(*current);

        for (auto adjacent : input.grid->get_adjacent_points(current->point)) {
            if (input.grid->get_square_unsafe(adjacent) == '#') {
                continue;
            }

            auto proposed_direction = adjacent - current->point;
            auto proposed_pwd =
                PointWithDirection(adjacent, proposed_direction);

            aoc_assert(std::abs(proposed_direction.dx) <= 1 &&
                           std::abs(proposed_direction.dy) <= 1,
                       "Invalid direction vector");

            int cost = 1;
            if (proposed_direction != current->direction) {
                cost += 1000;
            }

            int total_cost = current_cost + cost;
            auto cost_it = distances_from_start.find(proposed_pwd);
            
            if (cost_it->second > total_cost) {
                cost_it->second = total_cost;
                previous.erase(proposed_pwd);
                previous.emplace(proposed_pwd, *current);
            } else if (cost_it->second == total_cost) {
                previous.emplace(proposed_pwd, *current);
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

std::unordered_set<aoc::Point> shortest_path_points;

// NOLINTNEXTLINE(misc-no-recursion)
void print_paths_recurse(
    aoc::Grid &grid,
    const std::unordered_multimap<PointWithDirection, PointWithDirection>
        &subgraph,
    PointWithDirection point) {

    grid.set_square(point.point, 'o');
    shortest_path_points.insert(point.point);

    if (subgraph.contains(point)) {
        auto [begin, end] = subgraph.equal_range(point);

        auto diff = std::distance(begin, end);
        std::cout << "Scanning " << diff << " paths" << std::endl;

        for (auto it = begin; it != end; it++) {
            print_paths_recurse(grid, subgraph, it->second);
        }
    }
}

void print_paths(const ParsedInput &input,
                 const std::unordered_multimap<PointWithDirection,
                                               PointWithDirection> &subgraph,
                 aoc::Point end) {
    auto new_grid = *input.grid;

    for (auto dir : directions) {
        auto pwd = PointWithDirection(end, dir);
        print_paths_recurse(new_grid, subgraph, pwd);
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

    return static_cast<int>(shortest_path_points.size());
}

} // namespace day16

namespace std {

size_t hash<day16::PointWithDirection>::operator()(
    const day16::PointWithDirection &pd) const {
    size_t seed = 0;

    aoc::hash_combine(seed, hash<aoc::Point>()(pd.point));
    aoc::hash_combine(seed, hash<aoc::Vector>()(pd.direction));

    return seed;
}

} // namespace std
