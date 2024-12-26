#ifndef AOC_2024_SEARCH_H
#define AOC_2024_SEARCH_H
#include "./grid.h"
#include <memory>
#include <optional>
#include <unordered_map>

namespace aoc {

std::optional<std::unordered_map<Point, Point>>
bfs(const std::unique_ptr<Grid> &grid, Point start, Point end);

}

#endif // AOC_2024_SEARCH_H
