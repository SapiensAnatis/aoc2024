//
// Created by jay on 01/01/25.
//
#include "day06.h"
#include <memory>
#include <unordered_set>

namespace day06::faster {

bool check_for_cycle(const std::shared_ptr<aoc::Grid> &grid, const aoc::Point &guard_start_point) {

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

int part2(const ParsedInput &input) {
    auto result = simulate_finite_guard_walk(input.grid, input.guard_start_point);
    int infinite_loop_opportunities = 0;

    for (auto &point : result.path) {
        input.grid->set_square(point.x, point.y, '#');
        if (check_for_cycle(input.grid, input.guard_start_point)) {
            infinite_loop_opportunities++;
        }
        input.grid->set_square(point.x, point.y, '.');
    }

    return infinite_loop_opportunities;
}

} // namespace day06::faster