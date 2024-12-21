#include "day12.h"
#include "../lib/hash.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace day12 {

ParsedInput parse_input(std::ifstream &input_stream) {
    return {aoc::parse_grid(input_stream)};
}

struct Region {
    int perimeter;
    int area;
    std::unordered_set<aoc::Point> points;
};

Region find_region_bfs(aoc::Point start, const ParsedInput &input) {
    std::queue<aoc::Point> queue;
    std::unordered_set<aoc::Point> explored;
    int perimeter = 0;

    queue.push(start);
    explored.insert(start);

    auto region_name = input.grid->get_square_unsafe(start);

    while (!queue.empty()) {
        auto v = queue.front();
        queue.pop();

        auto adjacent = input.grid->get_adjacent_points(v);

        // Add any perimeter that we get from the grid boundaries
        perimeter += (4 - static_cast<int>(adjacent.size()));

        for (auto edge : adjacent) {
            if (input.grid->get_square_unsafe(edge) != region_name) {
                perimeter++;
                continue;
            }

            if (explored.contains(edge)) {
                continue;
            }

            explored.insert(edge);
            queue.push(edge);
        }
    }

    return {perimeter, static_cast<int>(explored.size()), explored};
}

int part1(const ParsedInput &input) {
    std::unordered_set<aoc::Point> accounted_for_points;
    int total_price = 0;

    for (auto it = input.grid->begin(); it != input.grid->end(); it++) {
        aoc::Point point = input.grid->get_point(it);

        if (accounted_for_points.contains(point)) {
            continue;
        }

        char region_name = *it;
        auto region = find_region_bfs(point, input);

        std::cout << "Found region " << region_name
                  << " with perimeter: " << region.perimeter
                  << " and area: " << region.area << std::endl;

        int price = region.perimeter * region.area;
        total_price += price;

        accounted_for_points.insert(region.points.begin(), region.points.end());
    }

    return total_price;
}

struct Part2Region {
    int num_sides;
    int area;
    std::unordered_set<aoc::Point> points;
};

bool operator==(const Edge &a, const Edge &b) {
    return a.direction == b.direction && a.point == b.point;
}

std::optional<Edge> find_edge(std::unordered_multimap<aoc::Point, Edge> &map,
                              aoc::Point key, aoc::Direction direction) {
    const auto [start, end] = map.equal_range(key);
    auto matching = std::find_if(start, end, [direction](const auto &pair) {
        return pair.second.direction == direction;
    });

    if (matching == end) {
        return std::nullopt;
    }

    return matching->second;
}

int get_num_sides_from_edge_points(const std::vector<Edge> &edges) {
    std::unordered_set<Edge> accounted_for_edges;
    int edge_count = 0;

    std::unordered_multimap<aoc::Point, Edge> edges_by_point;

    for (const auto &edge : edges) {
        edges_by_point.emplace(edge.point, edge);
    }

    for (const auto &edge : edges) {
        if (accounted_for_edges.contains(edge)) {
            continue;
        }

        edge_count++;
        accounted_for_edges.insert(edge);

        bool horizontal = edge.direction == aoc::Direction::North ||
                          edge.direction == aoc::Direction::South;

        aoc::Vector positive_vec =
            horizontal ? aoc::Vector(1, 0) : aoc::Vector(0, 1);
        aoc::Vector negative_vec = -positive_vec;

        auto negative_sibling = find_edge(
            edges_by_point, edge.point + negative_vec, edge.direction);
        auto positive_sibling = find_edge(
            edges_by_point, edge.point + positive_vec, edge.direction);

        while (positive_sibling || negative_sibling) {
            if (positive_sibling) {
                accounted_for_edges.insert(*positive_sibling);
                positive_sibling = find_edge(
                    edges_by_point, positive_sibling->point + positive_vec,
                    edge.direction);
            }

            if (negative_sibling) {
                accounted_for_edges.insert(*negative_sibling);
                negative_sibling = find_edge(
                    edges_by_point, negative_sibling->point + negative_vec,
                    edge.direction);
            }
        }
    }

    return edge_count;
}

Part2Region find_region_bfs_part2(aoc::Point start, const ParsedInput &input) {
    std::queue<aoc::Point> queue;
    std::unordered_set<aoc::Point> explored;
    std::vector<Edge> edges;

    queue.push(start);
    explored.insert(start);

    auto region_name = input.grid->get_square_unsafe(start);

    while (!queue.empty()) {
        auto v = queue.front();
        queue.pop();

        aoc::Point north = {v.x, v.y - 1};
        aoc::Point east = {v.x + 1, v.y};
        aoc::Point south = {v.x, v.y + 1};
        aoc::Point west = {v.x - 1, v.y};

        if (input.grid->get_square(north) != region_name) {
            edges.emplace_back(aoc::Direction::North, v);
        }

        if (input.grid->get_square(east) != region_name) {
            edges.emplace_back(aoc::Direction::East, v);
        }

        if (input.grid->get_square(south) != region_name) {
            edges.emplace_back(aoc::Direction::South, v);
        }

        if (input.grid->get_square(west) != region_name) {
            edges.emplace_back(aoc::Direction::West, v);
        }

        std::array<aoc::Point, 4> adjacent{north, east, south, west};

        for (auto edge : adjacent) {
            if (input.grid->get_square(edge) != region_name) {
                continue;
            }

            if (explored.contains(edge)) {
                continue;
            }

            explored.insert(edge);
            queue.push(edge);
        }
    }

    int num_sides = get_num_sides_from_edge_points(edges);

    return {num_sides, static_cast<int>(explored.size()), explored};
}

int part2(const ParsedInput &input) {
    std::unordered_set<aoc::Point> accounted_for_points;
    int total_price = 0;

    for (auto it = input.grid->begin(); it != input.grid->end(); it++) {
        aoc::Point point = input.grid->get_point(it);

        if (accounted_for_points.contains(point)) {
            continue;
        }

        char region_name = *it;
        auto region = find_region_bfs_part2(point, input);

        std::cout << "Found region " << region_name
                  << " with sides: " << region.num_sides
                  << " and area: " << region.area << std::endl;

        int price = region.num_sides * region.area;
        total_price += price;

        accounted_for_points.insert(region.points.begin(), region.points.end());
    }

    return total_price;
}

} // namespace day12

namespace std {
size_t hash<day12::Edge>::operator()(const day12::Edge &e) const {
    size_t seed = 0;
    aoc::hash_combine(seed, e.point);
    aoc::hash_combine(seed, e.direction);

    return seed;
}
} // namespace std