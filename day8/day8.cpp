
#include "day8.h"

namespace day8 {

ParsedInput::ParsedInput(std::unique_ptr<aoc::Grid> grid)
    : grid(std::move(grid)) {}

ParsedInput parse_input(std::ifstream &input_stream) {
    auto grid = aoc::parse_grid(input_stream);
    return ParsedInput(std::move(grid));
}

struct Antenna {
    aoc::Point position;
    char frequency;
};

int part1(const ParsedInput &input) {
    std::vector<Antenna> antennae;
    for (auto it = input.grid->begin(); it != input.grid->end(); it++) {
        if (*it != '.') {
            antennae.emplace_back(aoc::Point(input.grid->get_point(it)), *it);
        }
    }

    return 0;
}

} // namespace day8