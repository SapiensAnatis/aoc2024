#include "day4.h"
#include <cassert>

namespace day4 {

aoc::Grid parse_input(std::ifstream &input) {
    std::vector<char> grid;
    std::string line;
    int width;

    std::getline(input, line);
    assert(!input.fail() && "Failed to read first line");
    width = static_cast<int>(line.length());
    std::copy(line.begin(), line.end(), std::back_inserter(grid));

    while (std::getline(input, line)) {
        std::copy(line.begin(), line.end(), std::back_inserter(grid));
    }

    return {grid, width};
}

bool can_find_xmas_in_direction(const aoc::Grid &grid, int x_origin,
                                int y_origin, int dx, int dy) {
    int x = x_origin;
    int y = y_origin;

    if (grid.get_square(x, y) != 'X') {
        return false;
    }

    x += dx;
    y += dy;

    if (grid.get_square(x, y) != 'M') {
        return false;
    }

    x += dx;
    y += dy;

    if (grid.get_square(x, y) != 'A') {
        return false;
    }

    x += dx;
    y += dy;

    if (grid.get_square(x, y) != 'S') {
        return false;
    }

    return true;
}

int part1(const aoc::Grid &grid) {
    int xmas_count = 0;

    for (int y = 0; y < grid.get_height(); y++) {
        for (int x = 0; x < grid.get_width(); x++) {
            // One 'X' square can lead to multiple occurrences of XMAS
            // North
            if (can_find_xmas_in_direction(grid, x, y, 0, -1)) {
                xmas_count++;
            }
            // North-east
            if (can_find_xmas_in_direction(grid, x, y, 1, -1)) {
                xmas_count++;
            }
            // East
            if (can_find_xmas_in_direction(grid, x, y, 1, 0)) {
                xmas_count++;
            }
            // South-east
            if (can_find_xmas_in_direction(grid, x, y, 1, 1)) {
                xmas_count++;
            }
            // South
            if (can_find_xmas_in_direction(grid, x, y, 0, 1)) {
                xmas_count++;
            }
            // South-west
            if (can_find_xmas_in_direction(grid, x, y, -1, 1)) {
                xmas_count++;
            }
            // West
            if (can_find_xmas_in_direction(grid, x, y, -1, 0)) {
                xmas_count++;
            }
            // North-west
            if (can_find_xmas_in_direction(grid, x, y, -1, -1)) {
                xmas_count++;
            }
        }
    }

    return xmas_count;
}

std::optional<std::string> get_diagonal_string(const aoc::Grid &grid,
                                               int x_origin, int y_origin,
                                               int dx, int dy) {
    char buffer[3];

    int x = x_origin - dx;
    int y = y_origin - dy;

    for (char &i : buffer) {
        if (auto square = grid.get_square(x, y)) {
            i = *square;
        } else {
            return std::nullopt;
        }

        x += dx;
        y += dy;
    }

    return std::string(buffer, 3);
}

bool can_find_x_shaped_mas(const aoc::Grid &grid, int x, int y) {
    if (grid.get_square(x, y) != 'A') {
        return false;
    }

    // Check +x +y and +x -y lines
    // +x +y: \     +x -y:   /
    //         \            /
    //          \          /
    auto plus_x_plus_y_str = get_diagonal_string(grid, x, y, 1, 1);
    if (plus_x_plus_y_str != "MAS" && plus_x_plus_y_str != "SAM") {
        return false;
    }

    auto plus_x_minus_y_str = get_diagonal_string(grid, x, y, 1, -1);
    if (plus_x_minus_y_str != "MAS" && plus_x_minus_y_str != "SAM") {
        return false;
    }

    return true;
}

int part2(const aoc::Grid &grid) {
    int x_shaped_mas_count = 0;

    for (int y = 0; y < grid.get_height(); y++) {
        for (int x = 0; x < grid.get_width(); x++) {
            if (can_find_x_shaped_mas(grid, x, y)) {
                x_shaped_mas_count++;
            }
        }
    }

    return x_shaped_mas_count;
}

} // namespace day4