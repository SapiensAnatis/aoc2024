
#include "day06.h"
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <utility>

namespace day6 {

struct Velocity {
    int x;
    int y;

    Velocity(int x, int y) : x(x), y(y) {}

    bool operator==(const Velocity &other) const;

    void rotate_90deg_clockwise() {
        // Matrix multiplication with rotational matrix:
        // x' = x cos(pi / 2) - y sin(pi / 2) = -y
        // y' = x sin(pi / 2) + y cos(pi / 2) = x
        int temp = this->x;
        this->x = -y;
        this->y = temp;
    }
};

bool Velocity::operator==(const Velocity &other) const {
    return this->x == other.x && this->y == other.y;
}

struct GuardState {
    aoc::Point position;
    Velocity direction;

    GuardState(aoc::Point position, Velocity direction)
        : position(position), direction(direction) {}
};

ParsedInput::ParsedInput(std::shared_ptr<aoc::Grid> grid,
                         aoc::Point guard_start_point)
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

std::unordered_set<aoc::Point>
simulate_finite_guard_walk(const std::shared_ptr<aoc::Grid> &grid,
                           const aoc::Point &guard_start_point) {
    GuardState state(guard_start_point, Velocity(0, -1));
    std::unordered_set<aoc::Point> visited_squares{guard_start_point};

    while (true) {
        int proposed_next_x = state.position.x + state.direction.x;
        int proposed_next_y = state.position.y + state.direction.y;
        std::optional<char> next_square =
            grid->get_square(proposed_next_x, proposed_next_y);

        if (next_square == '#') {
            // Obstacle hit, turn right
            state.direction.rotate_90deg_clockwise();
        } else if (next_square) {
            state.position.x += state.direction.x;
            state.position.y += state.direction.y;
            visited_squares.insert(state.position);
        } else {
            break;
        }
    }

    return visited_squares;
}

bool check_for_cycle(const std::shared_ptr<aoc::Grid> &grid,
                     const aoc::Point &guard_start_point) {
    auto advance_state = [&grid](GuardState &state) {
        int proposed_next_x = state.position.x + state.direction.x;
        int proposed_next_y = state.position.y + state.direction.y;
        std::optional<char> next_square =
            grid->get_square(proposed_next_x, proposed_next_y);

        if (next_square == '#') {
            // Obstacle hit, turn right
            state.direction.rotate_90deg_clockwise();
        } else {
            state.position.x += state.direction.x;
            state.position.y += state.direction.y;
        }
    };

    GuardState hare_state(guard_start_point, Velocity(0, -1));
    GuardState tortoise_state(guard_start_point, Velocity(0, -1));

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
    auto path = simulate_finite_guard_walk(input.grid, input.guard_start_point);
    return static_cast<int>(path.size());
}

int part2(const ParsedInput &input) {
    auto path = simulate_finite_guard_walk(input.grid, input.guard_start_point);
    int infinite_loop_opportunities = 0;

    for (auto &point : path) {
        std::shared_ptr<aoc::Grid> grid_with_obstacle_here =
            input.grid->with_mutation(point.x, point.y, '#');
        if (check_for_cycle(grid_with_obstacle_here, input.guard_start_point)) {
            infinite_loop_opportunities++;
        }
    }

    return infinite_loop_opportunities;
}

} // namespace day6