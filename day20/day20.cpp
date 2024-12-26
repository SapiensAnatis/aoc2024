#include "day20.h"
#include "../lib/grid.h"
#include "../lib/search.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <unordered_set>

namespace day20 {

ParsedInput parse_input(std::ifstream &input_stream) {
    auto grid = aoc::parse_grid(input_stream);

    return {.grid = std::move(grid)};
}

std::vector<aoc::Point>
get_adjacent_squares_radius_2(const std::unique_ptr<aoc::Grid> &grid,
                              aoc::Point origin) {
    std::vector<aoc::Point> result;

    for (int dy = -2; dy <= 2; dy++) {
        for (int dx = -2; dx <= 2; dx++) {
            aoc::Point point(origin.x + dx, origin.y + dy);
            int distance = std::abs(dx) + std::abs(dy);

            if (distance > 2) {
                continue;
            }

            if (point == origin || !grid->get_square(point)) {
                continue;
            }

            result.push_back(point);
        }
    }

    return result;
}

int part1(const ParsedInput &input) {
    auto start_it = std::find(input.grid->begin(), input.grid->end(), 'S');
    auto start = input.grid->get_point(start_it);

    auto end_it = std::find(input.grid->begin(), input.grid->end(), 'E');
    auto end = input.grid->get_point(end_it);

    input.grid->set_square(start, '.');
    input.grid->set_square(end, '.');

    auto parents = aoc::bfs(input.grid, start, end);

    if (!parents) {
        throw std::runtime_error("Could not find path");
    }

    std::vector path{end};
    aoc::Point current_node = parents->at(end);

    while (current_node != start) {
        path.push_back(current_node);
        current_node = parents->at(current_node);
    }

    path.push_back(current_node);

    std::unordered_map<aoc::Point, int> path_positions;
    path_positions.reserve(path.size());

    int time = 0;
    for (auto path_point : std::ranges::reverse_view(path)) {
        path_positions[path_point] = time;
        time++;
    }

    std::map<int, int> possible_cheat_values;

    for (auto [path_point, time] : path_positions) {
        auto candidate_squares =
            get_adjacent_squares_radius_2(input.grid, path_point);

        for (auto candidate_cheat_dest : candidate_squares) {
            auto new_path_point_it = path_positions.find(candidate_cheat_dest);
            if (new_path_point_it == path_positions.end()) {
                continue;
            }

            auto new_time = new_path_point_it->second;

            // A cheat's value is the progress it gains, minus two for the time
            // taken to conduct the cheat
            auto cheat_value = new_time - time - 2;

            if (cheat_value <= 0) {
                // We would be going backwards or not moving - not a very good
                // cheat
                continue;
            }

            // if (cheat_value >= 40) {
            //     std::cout << "Found cheat with value " << cheat_value
            //               << std::endl;
            //
            //     auto grid_copy = *input.grid;
            //
            //     std::cout << grid_copy << std::endl;
            //
            //     grid_copy.set_square(candidate_cheat_dest, 'Y');
            //     grid_copy.set_square(path_point, 'X');
            //
            //     std::cout << grid_copy << std::endl;
            // }

            auto [it, _] = possible_cheat_values.emplace(cheat_value, 0);
            it->second++;
        }
    }

    int num_cheats_over_100 = 0;
    for (const auto [cheat_value, num_cheats] : possible_cheat_values) {
        std::cout << "Found " << num_cheats << " cheat(s) that would save "
                  << cheat_value << " picoseconds" << std::endl;

        if (cheat_value >= 100) {
            num_cheats_over_100 += num_cheats;
        }
    }

    return num_cheats_over_100;
}

} // namespace day20
