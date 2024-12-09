
#include "day6.h"
#include <iostream>
#include <set>
#include <utility>

namespace day6 {

struct Velocity {
    int x;
    int y;

    Velocity(int x, int y) : x(x), y(y) {}

    void rotate_90deg_clockwise() {
        // Matrix multiplication with rotational matrix:
        // x' = x cos(pi / 2) - y sin(pi / 2) = -y
        // y' = x sin(pi / 2) + y cos(pi / 2) = x
        int temp = this->x;
        this->x = -y;
        this->y = temp;
    }
};

struct GuardState {
    aoc::Point position;
    Velocity direction;

    GuardState(aoc::Point position, Velocity direction)
        : position(std::move(position)), direction(direction) {}
};

ParsedInput::ParsedInput(std::shared_ptr<aoc::Grid> grid,
                         aoc::Point guard_start_point)
    : grid(std::move(grid)), guard_start_point(std::move(guard_start_point)) {}

ParsedInput parse_input(std::ifstream &input) {
    auto grid = aoc::parse_grid(input);
    auto guard_start = grid->find_character('^');

    if (!guard_start) {
        std::cerr << "Failed to find guard\n";
        exit(1);
    }

    return {std::move(grid), *guard_start};
}

int simulate_finite_guard_walk(const ParsedInput &input) {
    GuardState state(input.guard_start_point, Velocity(0, -1));
    std::set<aoc::Point> visited_squares{input.guard_start_point};

    while (true) {
        int proposed_next_x = state.position.x + state.direction.x;
        int proposed_next_y = state.position.y + state.direction.y;
        std::optional<char> next_square =
            input.grid->get_square(proposed_next_x, proposed_next_y);

        if (next_square == '#') {
            // Obstacle hit, turn right
            state.direction.rotate_90deg_clockwise();
        } else if (next_square) {
            state.position.x += state.direction.x;
            state.position.y += state.direction.y;
            auto [it, added] = visited_squares.insert(state.position);
            std::cout << std::boolalpha << "Reached position " << state.position
                      << ". Added: " << added << "\n";
        } else {
            break;
        }
    }

    return static_cast<int>(visited_squares.size());
}

int part1(const ParsedInput &input) {
    return simulate_finite_guard_walk(input);
}

} // namespace day6