#ifndef AOC2024_DAY14_H
#define AOC2024_DAY14_H

#include "../lib/grid.h"

namespace day14 {

enum class GridQuadrant {
    NorthEast,
    NorthWest,
    SouthEast,
    SouthWest,
    Ambiguous // on the midpoint line of one or both axes
};

class Robot {
  public:
    Robot(aoc::Point position, aoc::Vector velocity,
          std::shared_ptr<aoc::Grid> grid_ptr);
    [[nodiscard]] aoc::Point get_position() const;
    [[nodiscard]] GridQuadrant calculate_quadrant() const;

    void walk();

  private:
    aoc::Point position;
    aoc::Vector velocity;
    std::shared_ptr<aoc::Grid> grid_ptr;
};

struct ParsedInput {
    std::vector<Robot> robots;
};

ParsedInput parse_input(std::ifstream &input_stream,
                        const std::shared_ptr<aoc::Grid> &grid);

int part1(const ParsedInput &input);

} // namespace day14

#endif // AOC2024_DAY14_H
