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
        next_square.x %= this->grid_width;
        next_square.y %= this->grid_height;

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
    for (; second < 100000; second++) {

        // todo: hoist this alloc?
        std::unordered_map<aoc::Point, int> robot_positions;

        for (auto &robot : robots) {
            robot.walk();

            auto [it, inserted] = robot_positions.emplace(robot.get_position(), 0);
            it->second++;
        }

        // CHEATED - had to look this up, otherwise I would have printed out
        // several thousand grids and checked them myself

        // todo: can merge this check with the for loop above (don't return early though)
        if (std::all_of(robot_positions.begin(), robot_positions.end(),
                        [](const auto &pair) { return pair.second == 1; })) {
            break;
        }
    }

    return second + 1; // elapsed seconds
}

} // namespace day14::faster