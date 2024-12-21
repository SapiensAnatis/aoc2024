#include "day14.h"
#include "../lib/assert.h"
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <unordered_map>

namespace day14 {

Robot::Robot(aoc::Point position, aoc::Vector velocity,
             std::shared_ptr<aoc::Grid> grid_ptr)
    : position(position), velocity(velocity), grid_ptr(std::move(grid_ptr)) {}

aoc::Point Robot::get_position() const { return this->position; }

void Robot::walk() {
    aoc::Point next_square = this->position + this->velocity;

    if (next_square.x >= this->grid_ptr->get_width()) {
        next_square.x -= this->grid_ptr->get_width();
    } else if (next_square.x < 0) {
        next_square.x += this->grid_ptr->get_width();
    }

    if (next_square.y >= this->grid_ptr->get_height()) {
        next_square.y -= this->grid_ptr->get_height();
    } else if (next_square.y < 0) {
        next_square.y += this->grid_ptr->get_height();
    }

    this->position = next_square;
}

GridQuadrant Robot::calculate_quadrant() const {
    auto half_width = (this->grid_ptr->get_width() - 1) / 2;
    auto half_height = (this->grid_ptr->get_height() - 1) / 2;

    if (this->position.x == half_width || this->position.y == half_height) {
        // Midpoint
        return GridQuadrant::Ambiguous;
    }

    if (this->position.y < half_height) {
        return this->position.x < half_width ? GridQuadrant::NorthEast
                                             : GridQuadrant::NorthWest;
    } else {
        return this->position.x < half_width ? GridQuadrant::SouthEast
                                             : GridQuadrant::SouthWest;
    }
}

ParsedInput parse_input(std::ifstream &input_stream,
                        const std::shared_ptr<aoc::Grid> &grid) {
    std::regex x_y_regex(R"(=(-?\d+),(-?\d+))");
    std::string line;

    std::vector<Robot> robots;

    while (std::getline(input_stream, line)) {
        auto x_y_begin =
            std::sregex_iterator(line.begin(), line.end(), x_y_regex);
        auto x_y_end = std::sregex_iterator();
        aoc_assert(std::distance(x_y_begin, x_y_end) == 2,
                   "x, y regex did not match enough times");

        const auto &position_match = *x_y_begin;
        aoc_assert(position_match.size() == 3,
                   "position match had too few capture groups");
        int position_x = std::stoi(position_match.str(1));
        int position_y = std::stoi(position_match.str(2));

        const auto &velocity_match = *(++x_y_begin);
        aoc_assert(velocity_match.size() == 3,
                   "velocity match had too few capture groups");
        int velocity_x = std::stoi(velocity_match.str(1));
        int velocity_y = std::stoi(velocity_match.str(2));

        robots.emplace_back(aoc::Point(position_x, position_y),
                            aoc::Vector(velocity_x, velocity_y), grid);
    }

    return {robots};
}

int part1(const ParsedInput &input) {
    auto robots_copy = input.robots;

    for (int second = 0; second < 100; second++) {
        for (auto &robot : robots_copy) {
            robot.walk();
        }
    }

    std::unordered_map<GridQuadrant, int> quadrant_scores = {
        {GridQuadrant::NorthEast, 0},
        {GridQuadrant::NorthWest, 0},
        {GridQuadrant::SouthEast, 0},
        {GridQuadrant::SouthWest, 0}};

    std::unordered_map<aoc::Point, int> robot_positions;

    for (auto &robot : robots_copy) {
        auto [it, _] = robot_positions.emplace(robot.get_position(), 0);
        it->second++;

        auto quadrant = robot.calculate_quadrant();
        if (quadrant == GridQuadrant::Ambiguous) {
            continue;
        }

        quadrant_scores[quadrant]++;
    }

    return std::accumulate(
        quadrant_scores.begin(), quadrant_scores.end(), 1,
        [](int acc, const auto &pair) { return acc * pair.second; });
}

} // namespace day14
