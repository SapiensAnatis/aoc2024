//
// Created by jay on 01/01/25.
//
#include "day14.h"
#include <algorithm>
#include <unordered_set>

namespace day14::faster {

class RobotV2 {
  public:
    RobotV2(aoc::Point position, aoc::Vector velocity, const std::shared_ptr<aoc::Grid> &grid_ptr)
        : position(position), velocity(velocity), grid_height(grid_ptr->get_height()),
          grid_width(grid_ptr->get_width()) {}

    [[nodiscard]] aoc::Point get_position() const { return this->position; };

    void walk() {
        aoc::Point next_square = this->position + this->velocity;
        next_square.x %= grid_width;
        next_square.y %= grid_height;

        if (next_square.x < 0) {
            next_square.x += this->grid_width;
        }

        if (next_square.y < 0) {
            next_square.y += this->grid_height;
        }

        this->position = next_square;
    }

  private:
    aoc::Point position;
    aoc::Vector velocity;
    int grid_height;
    int grid_width;
};

int part2(const ParsedInput &input) {
    std::shared_ptr grid = aoc::Grid::create('.', 101, 103);

    std::vector<RobotV2> robots;
    robots.reserve(input.robot_positions.size());

    for (const auto &robot_pos : input.robot_positions) {
        robots.emplace_back(robot_pos.position, robot_pos.velocity, grid);
    }

    int second = 0;
    std::unordered_set<aoc::Point> robot_positions;
    robot_positions.reserve(robots.size());

    for (; second < 100000; second++) {
        robot_positions.clear();

        bool all_unique = true;

        for (auto &robot : robots) {
            robot.walk();
            all_unique = all_unique && robot_positions.insert(robot.get_position()).second;
        }

        if (all_unique) {
            break;
        }
    }

    return second + 1; // elapsed seconds
}

} // namespace day14::faster