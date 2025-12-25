#ifndef AOC2024_DAY16_H
#define AOC2024_DAY16_H

#include "../lib/grid.h"

namespace day16 {

struct ParsedInput {
    std::unique_ptr<aoc::Grid> grid;
};

struct PointWithDirection {
    aoc::Point point{0, 0};
    aoc::Vector direction{0, 0};
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);
int part2(const ParsedInput &input);

} // namespace day16

namespace std {
template <> struct hash<day16::PointWithDirection> {
    size_t operator()(const day16::PointWithDirection &pd) const;
};
} // namespace std

#endif // AOC2024_DAY16_H
