
#include "day06.h"

#include "../lib/assert.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace day06 {

struct Velocity {
    int x;
    int y;

    Velocity(int x, int y) : x(x), y(y) {}

    bool operator==(const Velocity &other) const;
};

bool Velocity::operator==(const Velocity &other) const {
    return this->x == other.x && this->y == other.y;
}

struct GuardState {
    aoc::Point position;
    aoc::Vector direction;

    GuardState(aoc::Point position, aoc::Vector direction)
        : position(position), direction(direction) {}
};

ParsedInput::ParsedInput(std::shared_ptr<aoc::Grid> grid, aoc::Point guard_start_point)
    : grid(std::move(grid)), guard_start_point(guard_start_point) {}

ParsedInput parse_input(std::ifstream &input) {
    auto grid = aoc::parse_grid(input);
    auto guard_start = std::find(grid->begin(), grid->end(), '^');

    if (guard_start == grid->end()) {
        std::cerr << "Failed to find guard\n";
        exit(1);
    }

    auto guard_start_point = grid->get_point(guard_start);

    return {std::move(grid), guard_start_point};
}

struct ObstacleHitResult {
    aoc::Point obstacle_position;
    aoc::Point guard_position;
    aoc::Vector new_direction;
};

struct GuardWalkResult {
    std::unordered_set<aoc::Point> path;
    std::vector<ObstacleHitResult> obstacles_hit;
};

GuardWalkResult simulate_finite_guard_walk(const std::shared_ptr<aoc::Grid> &grid,
                                           const aoc::Point &guard_start_point) {
    GuardState state(guard_start_point, aoc::Vector(0, -1));
    std::unordered_set path{guard_start_point};
    std::vector<ObstacleHitResult> obstacles_hit;

    while (true) {
        int proposed_next_x = state.position.x + state.direction.dx;
        int proposed_next_y = state.position.y + state.direction.dy;
        aoc::Point proposed_next_point(proposed_next_x, proposed_next_y);
        std::optional<char> next_square = grid->get_square(proposed_next_point);

        if (next_square == '#') {
            // Obstacle hit, turn right
            state.direction = state.direction.rotate_90deg_clockwise();
            obstacles_hit.emplace_back(proposed_next_point, state.position, state.direction);
        } else if (next_square) {
            path.insert(state.position);
            state.position.x += state.direction.dx;
            state.position.y += state.direction.dy;
        } else {
            break;
        }
    }

    return {.path = path, .obstacles_hit = obstacles_hit};
}

bool check_for_cycle(const std::shared_ptr<aoc::Grid> &grid, const aoc::Point &guard_start_point) {
    auto advance_state = [&grid](GuardState &state) {
        int proposed_next_x = state.position.x + state.direction.dx;
        int proposed_next_y = state.position.y + state.direction.dy;
        std::optional<char> next_square = grid->get_square(proposed_next_x, proposed_next_y);

        if (next_square == '#') {
            // Obstacle hit, turn right
            state.direction = state.direction.rotate_90deg_clockwise();
        } else {
            state.position.x += state.direction.dx;
            state.position.y += state.direction.dy;
        }
    };

    GuardState hare_state(guard_start_point, aoc::Vector(0, -1));
    GuardState tortoise_state(guard_start_point, aoc::Vector(0, -1));

    while (grid->get_square(hare_state.position)) {
        advance_state(hare_state);
        advance_state(hare_state);
        advance_state(tortoise_state);

        if (hare_state.position == tortoise_state.position &&
            hare_state.direction == tortoise_state.direction) {
            // The hare has lapped the tortoise - this is an infinite loop
            return true;
        }
    }

    // Hare has exited the grid
    return false;
}

int part1(const ParsedInput &input) {
    auto result = simulate_finite_guard_walk(input.grid, input.guard_start_point);
    return static_cast<int>(result.path.size());
}

int part2(const ParsedInput &input) {
    auto result = simulate_finite_guard_walk(input.grid, input.guard_start_point);
    int infinite_loop_opportunities = 0;
    std::vector<aoc::Point> infinite_loop_points;

    for (auto &point : result.path) {
        std::shared_ptr grid_with_obstacle_here = input.grid->with_mutation(point.x, point.y, '#');
        if (check_for_cycle(grid_with_obstacle_here, input.guard_start_point)) {
            infinite_loop_opportunities++;
            infinite_loop_points.push_back(point);
        }
    }

    return infinite_loop_opportunities;
}

std::optional<aoc::Point> find_adjacent_point_on_path(const std::shared_ptr<aoc::Grid> &grid,
                                                      const GuardWalkResult &result,
                                                      aoc::Point point) {
    auto adjacent = grid->get_adjacent_points(point);
    auto path_square_it =
        std::ranges::find_if(adjacent, [&result](aoc::Point p) { return result.path.contains(p); });

    if (path_square_it != adjacent.end()) {
        return *path_square_it;
    }

    return std::nullopt;
}

int faster::part2(const ParsedInput &input) {
    auto result = simulate_finite_guard_walk(input.grid, input.guard_start_point);

    std::unordered_multimap<int, aoc::Point> obstacles_by_x;
    std::unordered_multimap<int, aoc::Point> obstacles_by_y;

    for (auto &hit : result.obstacles_hit) {
        obstacles_by_x.emplace(hit.obstacle_position.x, hit.obstacle_position);
        obstacles_by_y.emplace(hit.obstacle_position.x, hit.obstacle_position);
    }

    /*
     * We're looking for a set of three obstacles that make up vertices of an 'almost-square', such
     * that completing the square would cause an infinite loop.
     * Something like:
     *
     * .#.......
     * .OOOOOOO#
     * .O.....O.
     * #OOOOOOO.
     * .......#.
     *
     * Let's label the obstacles as follows:
     * .A.......
     * .OOOOOOOB
     * .O.....O.
     * DOOOOOOO.
     * .......C.
     */

    std::vector<aoc::Point> infinite_loop_obstacles;

    for (auto &hit : result.obstacles_hit) {
        // Let's test assuming this is obstacle A, to avoid counting the same potential shape more
        // than once
        auto obstacle_a_position = hit.obstacle_position;

        // Go right until we find a new obstacle, or we reach the end of the grid
        aoc::Point obstacle_b_position = hit.guard_position;
        std::optional<char> obstacle_b_square = input.grid->get_square(obstacle_b_position);
        while (obstacle_b_square && obstacle_b_square != '#') {
            obstacle_b_position.x += 1;
            obstacle_b_square = input.grid->get_square(obstacle_b_position);
        }

        if (!obstacle_b_square) {
            // We hit the edge of the grid without finding another obstacle
            continue;
        }

        // Go down until we find obstacle C
        aoc::Point obstacle_c_position = obstacle_b_position - aoc::Vector(-1, 0);
        std::optional<char> obstacle_c_square = input.grid->get_square(obstacle_c_position);
        while (obstacle_c_square && obstacle_c_square != '#') {
            obstacle_c_position.y += 1;
            obstacle_c_square = input.grid->get_square(obstacle_c_position);
        }

        if (!obstacle_c_square) {
            continue;
        }

        // We have found obstacle A, B, and C - now we know we can make an infinite loop if we place
        // obstacle D at some coordinates
        aoc::Point obstacle_d_position(obstacle_a_position.x - 1, obstacle_c_position.y - 1);
        infinite_loop_obstacles.push_back(obstacle_d_position);

        std::shared_ptr grid_with_obstacle_here =
            input.grid->with_mutation(obstacle_d_position.x, obstacle_d_position.y, '#');
        if (!check_for_cycle(grid_with_obstacle_here, input.guard_start_point)) {
            aoc_assert(check_for_cycle(grid_with_obstacle_here, input.guard_start_point),
                       "failed to create infinite loop");
        }
    }

    return static_cast<int>(infinite_loop_obstacles.size());
}

} // namespace day06