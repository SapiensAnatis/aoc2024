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

struct RobotPosition {
    aoc::Point position;
    aoc::Vector velocity;
};

class Robot {
  public:
    Robot() : Robot(aoc::Point{0, 0}, aoc::Vector{0, 0}, nullptr) {}
    Robot(aoc::Point position, aoc::Vector velocity, std::shared_ptr<aoc::Grid> grid_ptr);
    [[nodiscard]] aoc::Point get_position() const;
    [[nodiscard]] GridQuadrant calculate_quadrant() const;

    void walk();

  private:
    aoc::Point position;
    aoc::Vector velocity;
    std::shared_ptr<aoc::Grid> grid_ptr;
};

struct ParsedInput {
    std::vector<RobotPosition> robot_positions;
};

ParsedInput parse_input(std::ifstream &input_stream);

int puzzle_part1(const ParsedInput &input, const std::shared_ptr<aoc::Grid> &grid);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);

} // namespace day14

namespace day14::faster {

int part2(const ParsedInput &input);

}

#endif // AOC2024_DAY14_H
