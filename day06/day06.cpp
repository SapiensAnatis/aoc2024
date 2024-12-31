
#include "day06.h"

#include "../lib/assert.h"
#include "../lib/hash.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace day06 {
struct GuardState {
    aoc::Point position;
    aoc::Vector direction;

    GuardState(aoc::Point position, aoc::Vector direction)
        : position(position), direction(direction) {}
};

bool operator==(const GuardState &a, const GuardState &b) {
    return a.position == b.position && a.direction == b.direction;
}

} // namespace day06

template <> struct std::hash<day06::GuardState> {
    size_t operator()(const day06::GuardState &state) const noexcept {
        size_t seed = 0;
        aoc::hash_combine(seed, state.position);
        aoc::hash_combine(seed, state.direction);

        return seed;
    }
};

namespace day06 {

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
            state.position.x += state.direction.dx;
            state.position.y += state.direction.dy;
            path.insert(state.position);
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

bool check_for_cycle_faster(const std::shared_ptr<aoc::Grid> &grid,
                            const aoc::Point &guard_start_point) {

    GuardState state(guard_start_point, aoc::Vector(0, -1));
    std::unordered_set<GuardState> obstacle_hit_states;
    obstacle_hit_states.reserve(150); // approximation from debugging

    while (grid->get_square(state.position)) {
        std::optional<char> next_square;
        int proposed_next_x = state.position.x;
        int proposed_next_y = state.position.y;

        // Teleport to the next obstacle
        do {
            proposed_next_x += state.direction.dx;
            proposed_next_y += state.direction.dy;
            next_square = grid->get_square(proposed_next_x, proposed_next_y);
        } while (next_square == '.' || next_square == '^');

        if (next_square == '#') {
            // Obstacle hit, turn right
            state.position.x = proposed_next_x - state.direction.dx;
            state.position.y = proposed_next_y - state.direction.dy;
            state.direction = state.direction.rotate_90deg_clockwise();

            auto [_, inserted] = obstacle_hit_states.insert(state);

            if (!inserted) {
                // We have hit this obstacle with the same direction before, we're looping
                return true;
            }
        } else if (next_square) {
            state.position.x = proposed_next_x;
            state.position.x = proposed_next_y;
        } else {
            break;
        }
    }

    // Guard has exited the grid
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

int faster::part2(const ParsedInput &input) {
    auto result = simulate_finite_guard_walk(input.grid, input.guard_start_point);
    int infinite_loop_opportunities = 0;

    for (auto &point : result.path) {
        input.grid->set_square(point.x, point.y, '#');
        if (check_for_cycle_faster(input.grid, input.guard_start_point)) {
            infinite_loop_opportunities++;
        }
        input.grid->set_square(point.x, point.y, '.');
    }

    return infinite_loop_opportunities;
}

} // namespace day06