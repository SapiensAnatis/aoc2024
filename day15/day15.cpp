#include "day15.h"

#include "../lib/assert.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace day15 {

ParsedInput parse_input(std::ifstream &input_stream) {
    std::stringstream grid;
    std::stringstream moves;

    std::string line;
    while (std::getline(input_stream, line) && !line.empty()) {
        grid << line << std::endl;
    }

    auto parsed_grid = aoc::parse_grid(grid);

    std::vector<aoc::Direction> parsed_moves;

    while (!input_stream.eof()) {
        char c;
        input_stream.get(c);

        switch (c) {
        case '^':
            parsed_moves.push_back(aoc::Direction::North);
            break;
        case '>':
            parsed_moves.push_back(aoc::Direction::East);
            break;
        case 'v':
            parsed_moves.push_back(aoc::Direction::South);
            break;
        case '<':
            parsed_moves.push_back(aoc::Direction::West);
            break;
        case '\n':
            break;
        default:
            std::cerr << "Invalid character in input: '" << c << "'"
                      << std::endl;
            exit(1);
        }
    }

    return {std::move(parsed_grid), parsed_moves};
}

bool try_move_obstacle(ParsedInput &input, aoc::Point obstacle_pos,
                       aoc::Vector offset) {
    auto candidate_pos = obstacle_pos + offset;
    while (std::optional<char> candidate_square =
               input.grid->get_square(candidate_pos) != '.') {
        if (candidate_square != 'O') {
            // Reached a wall or grid boundary
            return false;
        }

        candidate_pos = candidate_pos + offset;
    }

    aoc_assert(input.grid->get_square(candidate_pos) == '.',
               "Exited while loop with non-empty square");

    input.grid->set_square(candidate_pos, 'O');
    input.grid->set_square(obstacle_pos, '.');
    return true;
}

void move_robot(ParsedInput &input, aoc::Point old_pos, aoc::Point new_pos) {
    input.grid->set_square(old_pos, '.');
    input.grid->set_square(new_pos, '@');
}

int part1(ParsedInput &input) {
    auto robot_pos_it = std::find(input.grid->begin(), input.grid->end(), '@');
    aoc_assert(robot_pos_it != input.grid->end(), "Failed to find robot");

    auto robot_pos = input.grid->get_point(robot_pos_it);
    for (const auto move : input.moves) {
        std::cout << "Processing move..." << std::endl;

        aoc::Vector offset(move);
        aoc::Point new_robot_pos = robot_pos + offset;
        std::optional<char> new_robot_square =
            input.grid->get_square(new_robot_pos);

        aoc_assert(new_robot_square,
                   "Robot tried to move out of bounds - where are the walls?");

        if (new_robot_square == '.') {
            // Free
            move_robot(input, robot_pos, new_robot_pos);
            robot_pos = new_robot_pos;
            std::cout << "Robot moved to: " << new_robot_pos << std::endl;
            continue;
        } else if (new_robot_square == '#') {
            // Wall, cannot do anything
            std::cout << "Failed to move robot: wall encountered at"
                      << new_robot_pos << std::endl;
            continue;
        } else if (new_robot_square == 'O') {
            // We have an obstacle, try to move it
            if (!try_move_obstacle(input, new_robot_pos, offset)) {
                std::cout << "Failed to move robot: obstacle cannot be moved at"
                          << new_robot_pos << std::endl;
                continue;
            }

            std::cout << "Robot moved obstacle and moved to " << new_robot_pos
                      << std::endl;

            move_robot(input, robot_pos, new_robot_pos);
            robot_pos = new_robot_pos;
        }
    }

    return 0;
}

} // namespace day15
