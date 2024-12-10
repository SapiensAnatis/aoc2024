#ifndef AOC_2024_GRID_H
#define AOC_2024_GRID_H

#include <memory>
#include <optional>
#include <vector>

namespace aoc {

struct Point;

struct Vector {
    int dx;
    int dy;

    Vector(int dx, int dy);
};

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

    friend Point operator+(const Point &point, const Vector &vector);

    bool operator==(const Point &other) const;
    bool operator<(const Point &other) const;

  private:
    std::weak_ptr<const aoc::Grid> grid_ptr;
};

std::shared_ptr<Grid> parse_grid(std::ifstream &input);

} // namespace aoc

#endif // AOC_2024_GRID_H