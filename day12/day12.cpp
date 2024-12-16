#include "day12.h"
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

        for (auto edge : input.grid->get_adjacent_points(v)) {
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

} // namespace day12
