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
                  << " and area: " << region.area << "\n";

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

int get_num_sides_from_edge_points(const std::vector<Edge> &edges) {
    std::unordered_set<Edge> accounted_for_edges;
    int edge_count = 0;
    std::vector<std::pair<Edge, int>> edge_sizes;

    for (const auto &edge : edges) {
        if (accounted_for_edges.contains(edge)) {
            continue;
        }

        edge_count++;
        accounted_for_edges.insert(edge);

        aoc::Vector negative_vec{0, 0};
        aoc::Vector positive_vec{0, 0};

        if (edge.direction == aoc::Direction::North ||
            edge.direction == aoc::Direction::South) {
            negative_vec = {-1, 0};
            positive_vec = {1, 0};
        } else {
            negative_vec = {0, -1};
            positive_vec = {0, 1};
        }

        auto negative_sibling = std::find_if(
            edges.begin(), edges.end(), [&edge, &negative_vec](auto &e) {
                return e.direction == edge.direction &&
                       e.point == edge.point + negative_vec;
            });
        auto positive_sibling = std::find_if(
            edges.begin(), edges.end(), [&edge, &positive_vec](auto &e) {
                return e.direction == edge.direction &&
                       e.point == edge.point + positive_vec;
            });

        int size = 1;

        while (positive_sibling != edges.end() ||
               negative_sibling != edges.end()) {
            if (positive_sibling != edges.end()) {
                size++;
                accounted_for_edges.insert(*positive_sibling);
                positive_sibling = std::find_if(
                    edges.begin(), edges.end(),
                    [&positive_sibling, &positive_vec](auto &e) {
                        return e.direction == positive_sibling->direction &&
                               e.point ==
                                   (*positive_sibling).point + positive_vec;
                    });
            }
            if (negative_sibling != edges.end()) {
                size++;
                accounted_for_edges.insert(*negative_sibling);
                negative_sibling = std::find_if(
                    edges.begin(), edges.end(),
                    [&negative_sibling, &negative_vec](auto &e) {
                        return e.direction == negative_sibling->direction &&
                               e.point ==
                                   (*negative_sibling).point + negative_vec;
                    });
            }
        }

        edge_sizes.emplace_back(edge, size);
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
                  << " and area: " << region.area << "\n";

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