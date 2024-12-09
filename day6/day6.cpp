
#include "day6.h"
#include <iostream>

namespace day6 {
ParsedInput::ParsedInput(aoc::Grid grid, aoc::Point guard_start_point)
    : grid(std::move(grid)), guard_start_point(guard_start_point) {}

ParsedInput parse_input(std::ifstream &input) {
    auto grid = aoc::parse_grid(input);
    auto guard_start = grid.find_character('^');

    if (!guard_start) {
        std::cerr << "Failed to find guard\n";
        exit(1);
    }

    return {std::move(grid), *guard_start};
}
} // namespace day6