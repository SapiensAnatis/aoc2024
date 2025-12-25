#ifndef AOC2024_DAY12_H
#define AOC2024_DAY12_H

#include "../lib/grid.h"
#include <memory>

namespace day12 {

struct ParsedInput {
    std::unique_ptr<aoc::Grid> grid;
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);

struct Edge {
    aoc::Direction direction;
    aoc::Point point;
};

bool operator==(const Edge &a, const Edge &b);

} // namespace day12

namespace std {
template <> struct hash<day12::Edge> {
    size_t operator()(const day12::Edge &e) const;
};
} // namespace std

#endif // AOC2024_DAY12_H
