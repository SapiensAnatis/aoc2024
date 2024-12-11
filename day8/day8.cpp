
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
}

int part1(const ParsedInput &input) {
    std::vector<Antenna> antennae;
    
}

} // namespace day8