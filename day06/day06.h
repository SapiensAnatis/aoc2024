#ifndef AOC2024_DAY06_H
#define AOC2024_DAY06_H

#include "../lib/grid.h"

#include <unordered_set>

namespace day06 {

struct GuardState {
    aoc::Point position;
    aoc::Vector direction;

    GuardState(aoc::Point position, aoc::Vector direction)
        : position(position), direction(direction) {}
};

inline bool operator==(const GuardState &a, const GuardState &b) {
    return a.position == b.position && a.direction == b.direction;
}

struct ParsedInput {
    std::shared_ptr<aoc::Grid> grid;
    aoc::Point guard_start_point;

    ParsedInput(std::shared_ptr<aoc::Grid> grid, aoc::Point guard_start_point);
};

struct GuardWalkResult {
    std::unordered_set<aoc::Point> path;
};

ParsedInput parse_input(std::ifstream &input_stream);

GuardWalkResult simulate_finite_guard_walk(const std::shared_ptr<aoc::Grid> &grid,
                                           const aoc::Point &guard_start_point);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);

} // namespace day06

template <> struct std::hash<day06::GuardState> {
    size_t operator()(const day06::GuardState &state) const noexcept {
        size_t seed = 0;
        aoc::hash_combine(seed, state.position);
        aoc::hash_combine(seed, state.direction);

        return seed;
    }
};

namespace day06::faster {

int part2(const ParsedInput &input);

}

#endif // AOC2024_DAY06_H