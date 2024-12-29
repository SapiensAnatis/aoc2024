#include "day15.h"

#include "../lib/assert.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
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
            std::cerr << "Invalid character in input: '" << c << "'" << std::endl;
            exit(1);
        }
    }

    return {std::move(parsed_grid), parsed_moves};
}

bool try_move_obstacle(ParsedInput &input, aoc::Point obstacle_pos, aoc::Vector offset) {
    auto candidate_pos = obstacle_pos + offset;
    while (input.grid->get_square(candidate_pos) == 'O') {
        candidate_pos = candidate_pos + offset;
    }

    if (input.grid->get_square(candidate_pos) != '.') {
        // Next available square is not empty - is a wall or out of bounds
        return false;
    }

    input.grid->set_square(candidate_pos, 'O');
    input.grid->set_square(obstacle_pos, '.');
    return true;
}

void move_robot(const std::unique_ptr<aoc::Grid> &grid, aoc::Point old_pos, aoc::Point new_pos) {
    grid->set_square(old_pos, '.');
    grid->set_square(new_pos, '@');
}

int calculate_gps(aoc::Point point) { return point.y * 100 + point.x; }

int part1(ParsedInput &input) {
    auto robot_pos_it = std::find(input.grid->begin(), input.grid->end(), '@');
    aoc_assert(robot_pos_it != input.grid->end(), "Failed to find robot");

    auto robot_pos = input.grid->get_point(robot_pos_it);
    for (const auto move : input.moves) {
        std::cout << "Processing move..." << std::endl;
        // std::cout << *input.grid << std::endl;

        aoc::Vector offset(move);
        aoc::Point new_robot_pos = robot_pos + offset;
        std::optional<char> new_robot_square = input.grid->get_square(new_robot_pos);

        aoc_assert(new_robot_square, "Robot tried to move out of bounds - where are the walls?");

        if (new_robot_square == '.') {
            // Free
            move_robot(input.grid, robot_pos, new_robot_pos);
            robot_pos = new_robot_pos;
            std::cout << "Robot moved to: " << new_robot_pos << std::endl;
            continue;
        } else if (new_robot_square == '#') {
            // Wall, cannot do anything
            std::cout << "Failed to move robot: wall encountered at" << new_robot_pos << std::endl;
            continue;
        } else if (new_robot_square == 'O') {
            // We have an obstacle, try to move it
            if (!try_move_obstacle(input, new_robot_pos, offset)) {
                std::cout << "Failed to move robot: obstacle cannot be moved at" << new_robot_pos
                          << std::endl;
                continue;
            }

            std::cout << "Robot moved obstacle and moved to " << new_robot_pos << std::endl;

            move_robot(input.grid, robot_pos, new_robot_pos);
            robot_pos = new_robot_pos;
        }
    }

    int gps = 0;

    for (auto it = input.grid->begin(); it != input.grid->end(); it++) {
        if (*it == 'O') {
            gps += calculate_gps(input.grid->get_point(it));
        }
    }

    return gps;
}

struct ObstacleMoveOperation {
    aoc::Point old_pos;
    aoc::Point old_pos_2;
    aoc::Point new_pos;
    aoc::Point new_pos_2;
    char obstacle_char;
    char obstacle_char_2;
};

// NOLINTNEXTLINE(misc-no-recursion)
bool try_move_obstacle_recursive(const std::unique_ptr<aoc::Grid> &grid, aoc::Point obstacle_pos,
                                 aoc::Vector offset, std::queue<ObstacleMoveOperation> &ops) {
    auto obstacle_char = grid->get_square_unsafe(obstacle_pos);

    auto obstacle_pos_2 =
        obstacle_char == '[' ? obstacle_pos + aoc::Vector(1, 0) : obstacle_pos + aoc::Vector(-1, 0);
    auto obstacle_char_2 = grid->get_square_unsafe(obstacle_pos_2);

    aoc_assert(obstacle_char != obstacle_char_2, "Invalid character");

    auto candidate_pos = obstacle_pos + offset;
    auto candidate_pos_2 = obstacle_pos_2 + offset;
    auto candidate_square = grid->get_square(candidate_pos);
    auto candidate_square_2 = grid->get_square(candidate_pos_2);

    if (!candidate_square || !candidate_square_2 || candidate_square == '#' ||
        candidate_square_2 == '#') {
        return false;
    }

    if (candidate_pos != obstacle_pos_2) {
        if (candidate_square != '.' &&
            !try_move_obstacle_recursive(grid, candidate_pos, offset, ops)) {
            return false;
        }
    }

    if (candidate_pos_2 != obstacle_pos) {
        if (candidate_square_2 != '.' &&
            !try_move_obstacle_recursive(grid, candidate_pos_2, offset, ops)) {
            return false;
        }
    }

    std::cout << "Moving obstacle at " << obstacle_pos << " and " << obstacle_pos_2 << std::endl;

    // only do a change if all changes succeed
    ObstacleMoveOperation operation{.old_pos = obstacle_pos,
                                    .old_pos_2 = obstacle_pos_2,
                                    .new_pos = candidate_pos,
                                    .new_pos_2 = candidate_pos_2,
                                    .obstacle_char = obstacle_char,
                                    .obstacle_char_2 = obstacle_char_2};

    ops.push(operation);
    return true;
}

bool try_move_obstacle_part2(const std::unique_ptr<aoc::Grid> &grid, aoc::Point obstacle_pos,
                             aoc::Vector offset) {
    std::queue<ObstacleMoveOperation> ops;

    if (!try_move_obstacle_recursive(grid, obstacle_pos, offset, ops)) {
        return false;
    }

    // Make a copy of the queue and go through in two passes to avoid operations
    // overwriting characters set by other operations
    auto ops_copy = ops;

    while (!ops.empty()) {
        auto op = ops.front();
        ops.pop();

        grid->set_square(op.old_pos, '.');
        grid->set_square(op.old_pos_2, '.');
    }

    while (!ops_copy.empty()) {
        auto op = ops_copy.front();
        ops_copy.pop();

        grid->set_square(op.new_pos, op.obstacle_char);
        grid->set_square(op.new_pos_2, op.obstacle_char_2);
    }

    return true;
}

int part2(const ParsedInput &input) {
    std::vector<char> new_grid_squares;
    new_grid_squares.reserve(input.grid->get_width() * 2 * input.grid->get_height());

    for (auto ch : *input.grid) {

        switch (ch) {
        case '#':
            new_grid_squares.push_back('#');
            new_grid_squares.push_back('#');
            break;
        case 'O':
            new_grid_squares.push_back('[');
            new_grid_squares.push_back(']');
            break;
        case '.':
            new_grid_squares.push_back('.');
            new_grid_squares.push_back('.');
            break;
        case '@':
            new_grid_squares.push_back('@');
            new_grid_squares.push_back('.');
            break;
        default:
            std::cerr << "Unknown character: '" << ch << "'" << std::endl;
            exit(1);
        }
    }

    auto grid = std::make_unique<aoc::Grid>(new_grid_squares, input.grid->get_width() * 2);

    auto robot_pos_it = std::find(grid->begin(), grid->end(), '@');
    aoc_assert(robot_pos_it != grid->end(), "Failed to find robot");

    // int counter = 0;

    auto robot_pos = grid->get_point(robot_pos_it);
    for (const auto move : input.moves) {
        // counter++;

        // std::string filename = std::to_string(counter) + ".txt";
        // std::ofstream grid_file(filename);
        //
        // grid_file << "Next move: " << move << std::endl;
        //
        // grid_file << *grid << std::endl;
        // grid_file.close();

        std::cout << "Processing move..." << move << std::endl;

        aoc::Vector offset(move);
        aoc::Point new_robot_pos = robot_pos + offset;
        std::optional<char> new_robot_square = grid->get_square(new_robot_pos);

        aoc_assert(new_robot_square, "Robot tried to move out of bounds - where are the walls?");

        if (new_robot_square == '.') {
            // Free
            move_robot(grid, robot_pos, new_robot_pos);
            robot_pos = new_robot_pos;
            std::cout << "Robot moved to: " << new_robot_pos << std::endl;
            continue;
        } else if (new_robot_square == '#') {
            // Wall, cannot do anything
            std::cout << "Failed to move robot: wall encountered at" << new_robot_pos << std::endl;
            continue;
        } else if (new_robot_square == '[' || new_robot_square == ']') {
            // We have an obstacle, try to move it
            if (!try_move_obstacle_part2(grid, new_robot_pos, offset)) {
                std::cout << "Failed to move robot: obstacle cannot be moved at" << new_robot_pos
                          << std::endl;
                continue;
            }

            std::cout << "Robot moved obstacle and moved to " << new_robot_pos << std::endl;

            move_robot(grid, robot_pos, new_robot_pos);
            robot_pos = new_robot_pos;
        }
    }

    int gps = 0;

    for (auto it = grid->begin(); it != grid->end(); it++) {
        if (*it == '[') {
            gps += calculate_gps(grid->get_point(it));
        }
    }

    return gps;
}

} // namespace day15
