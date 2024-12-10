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

class Grid {
  public:
    static std::unique_ptr<Grid> create(std::vector<char> squares, int width) {
        return std::make_unique<Grid>(std::move(squares), width);
    }

    Grid(std::vector<char> squares, int width);

    [[nodiscard]] std::optional<char> get_square(int x, int y) const;
    [[nodiscard]] std::optional<char> get_square(const Point &point) const;
    [[nodiscard]] int get_width() const;
    [[nodiscard]] int get_height() const;
    [[nodiscard]] std::unique_ptr<Grid> with_mutation(int x, int y,
                                                      char new_value);

    // TODO: Consider making an iterator to enable std::find?
    [[nodiscard]] std::optional<Point> find_character(char to_find) const;

  private:
    [[nodiscard]] int calculate_array_index(int x, int y) const;

    int width;
    int height;
    std::vector<char> squares;
};

struct Point {
    int x;
    int y;

    Point(int x, int y);

    friend Point operator+(const Point &point, const Vector &vector);

    bool operator==(const Point &other) const;
};

std::ostream &operator<<(std::ostream &stream, const Point &point);

std::unique_ptr<Grid> parse_grid(std::ifstream &input);

} // namespace aoc

namespace std {
template <> struct hash<aoc::Point> {
    size_t operator()(const aoc::Point &p) const;
};
} // namespace std

#endif // AOC_2024_GRID_H