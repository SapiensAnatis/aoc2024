//
// Created by jay on 26/12/24.
//

#include "search.h"

#include <queue>
#include <unordered_set>

namespace aoc {

std::optional<std::unordered_map<Point, Point>> bfs(const std::unique_ptr<Grid> &grid, Point start,
                                                    Point end) {
    std::queue<Point> queue;
    std::unordered_set<Point> explored;
    std::unordered_map<Point, Point> parents;
    explored.insert(start);
    queue.push(start);

    while (!queue.empty()) {
        Point current = queue.front();
        queue.pop();

        if (current == end) {
            return parents;
        }

        for (auto edge : grid->get_adjacent_points(current)) {
            if (grid->get_square_unsafe(edge) != '.') {
                continue;
            }

            if (explored.contains(edge)) {
                continue;
            }

            explored.insert(edge);
            parents[edge] = current;
            queue.push(edge);
        }
    }

    // No path found
    return std::nullopt;
}

} // namespace aoc