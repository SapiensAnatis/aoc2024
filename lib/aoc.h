//
// Created by jay on 03/12/24.
//

#ifndef AOC2024_AOC_H
#define AOC2024_AOC_H

#include <fstream>
#include <memory>
#include <optional>
#include <string_view>
#include <utility>
#include <vector>

namespace aoc {

struct Point;

class Grid : public std::enable_shared_from_this<Grid> {
  public:
    static std::shared_ptr<Grid> create(std::vector<char> squares, int width) {
        return std::make_shared<Grid>(std::move(squares), width);
    }

    Grid(std::vector<char> squares, int width);

    Grid(const Grid &) = delete;

    [[nodiscard]] std::optional<char> get_square(int x, int y) const;
    [[nodiscard]] std::optional<char> get_square(const Point &point) const;
    [[nodiscard]] int get_width() const;
    [[nodiscard]] int get_height() const;
    [[nodiscard]] std::shared_ptr<Grid> with_mutation(int x, int y,
                                                      char new_value);

    // TODO: Consider making an iterator to enable std::find?
    [[nodiscard]] std::optional<Point> find_character(char to_find) const;

  private:
    int calculate_array_index(int x, int y) const;

    int width;
    int height;
    std::vector<char> squares;
};

struct Point {
    int x;
    int y;

    Point(int x, int y, const std::weak_ptr<const Grid> &grid_ref);

    friend std::ostream &operator<<(std::ostream &stream, Point const &point);

    bool operator==(const Point &other) const;
    bool operator<(const Point &other) const;

  private:
    std::weak_ptr<const aoc::Grid> grid_ptr;
};

std::shared_ptr<Grid> parse_grid(std::ifstream &input);

std::ifstream get_example_ifstream();

std::ifstream get_example_ifstream(int example_num);

std::ifstream get_real_ifstream();

std::optional<long> stol(const std::string_view &input);

std::optional<int> stoi(const std::string_view &input);

std::vector<std::string_view> split(const std::string_view &str,
                                    char separator);

std::vector<std::string_view> split(const std::string &str, char separator);
} // namespace aoc

#endif // AOC2024_AOC_H
