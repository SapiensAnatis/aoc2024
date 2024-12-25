#include "day18.h"

#include "../lib/aoc.h"
#include "../lib/assert.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace day18 {

ParsedInput parse_input(std::ifstream &input_stream) {
    std::string line;
    std::vector<aoc::Point> byte_fall_points;

    while (std::getline(input_stream, line)) {
        auto split = aoc::split(line, ',');
        aoc_assert(split.size() == 2, "Unexpected line split result");

        int x = aoc::parse_int(split[0]);
        int y = aoc::parse_int(split[1]);

        byte_fall_points.emplace_back(x, y);
    }

    return {.byte_positions = byte_fall_points};
}

std::unordered_map<aoc::Point, aoc::Point>
bfs(const std::unique_ptr<aoc::Grid> &grid, aoc::Point start) {
    std::queue<aoc::Point> queue;
    std::unordered_set<aoc::Point> explored;
    std::unordered_map<aoc::Point, aoc::Point> parents;
    explored.insert(start);
    queue.push(start);

    while (!queue.empty()) {
        aoc::Point current = queue.front();
        queue.pop();

        bool is_goal = current.x == grid->get_width() - 1 &&
                       current.y == grid->get_height() - 1;

        if (is_goal) {
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

    throw std::runtime_error("No path found");
}

std::vector<aoc::Point>
get_bfs_path(const std::unordered_map<aoc::Point, aoc::Point> &bfs_result,
             const aoc::Point &end) {
    auto parent = bfs_result.at(end);
    std::vector<aoc::Point> path;

    while (!(parent.x == 0 && parent.y == 0)) {
        path.push_back(parent);
        parent = bfs_result.at(parent);
    }

    path.push_back(parent);

    return {path.rbegin(), path.rend()};
}

int part1(const ParsedInput &input, int grid_size, int num_bytes_fall) {

    aoc_assert(num_bytes_fall < static_cast<int>(input.byte_positions.size()),
               "Cannot simulate beyond end of input byte positions");

    auto grid = aoc::Grid::create('.', grid_size, grid_size);

    for (int i = 0; i < num_bytes_fall; i++) {
        aoc::Point point = input.byte_positions[i];
        grid->set_square(point, '#');
    }

    std::cout << *grid << std::endl;

    aoc::Point start = {0, 0};
    aoc::Point end = {grid->get_width() - 1, grid->get_height() - 1};

    auto bfs_result = bfs(grid, start);
    auto bfs_path = get_bfs_path(bfs_result, end);

    for (auto point : bfs_path) {
        grid->set_square(point, 'O');
    }

    std::cout << *grid << std::endl;

    return static_cast<int>(bfs_path.size());
}

} // namespace day18
