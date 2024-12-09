//
// Created by jay on 03/12/24.
//

#ifndef AOC2024_AOC_H
#define AOC2024_AOC_H

#include <fstream>
#include <optional>
#include <string_view>
#include <vector>

namespace aoc {

struct Point {
    int x;
    int y;

    bool operator==(const Point &other) const;
    bool operator<(const Point &other) const;
};

class Grid {
  public:
    Grid(std::vector<char> squares, int width);

    [[nodiscard]] std::optional<char> get_square(int x, int y) const;
    [[nodiscard]] std::optional<char> get_square(Point point) const;
    [[nodiscard]] int get_width() const;
    [[nodiscard]] int get_height() const;

    // TODO: Consider making an iterator to enable std::find?
    [[nodiscard]] std::optional<Point> find_character(char to_find) const;

  private:
    int width;
    int height;
    std::vector<char> squares;
};

Grid parse_grid(std::ifstream &input);

std::ifstream get_example_ifstream();

std::ifstream get_example_ifstream(int example_num);

std::ifstream get_real_ifstream();

std::optional<int> stoi(const std::string_view &input);

std::vector<std::string_view> split(const std::string &str, char separator);
} // namespace aoc

#endif // AOC2024_AOC_H
