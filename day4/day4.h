#ifndef AOC2024_DAY4_H
#define AOC2024_DAY4_H

#include <iostream>
#include <optional>
#include <vector>

namespace day4 {

// TODO: make shared if needed
    class Grid {
    public:
        Grid(const std::vector<char> &squares, int width) {
            this->squares = squares;
            this->width = width;
            this->height = static_cast<int>(squares.size()) / this->width;
        }

        [[nodiscard]] std::optional<char> get_square(int x, int y) const;

        int width;
        int height;

    private:
        std::vector<char> squares;
    };

    Grid parse_input(std::ifstream &input);

    int part1(const Grid &grid);

    int part2(const Grid &grid);

} // namespace day4

#endif // AOC2024_DAY4_H