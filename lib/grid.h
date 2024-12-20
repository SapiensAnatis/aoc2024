#ifndef AOC_2024_GRID_H
#define AOC_2024_GRID_H

#include <iterator>
#include <memory>
#include <optional>
#include <vector>

namespace aoc {

struct Point;

struct Vector {
    int dx;
    int dy;

    Vector(int dx, int dy);

    Vector operator-() const;
};

class Grid {
  public:
    static std::unique_ptr<Grid> create(std::vector<char> squares, int width) {
        return std::make_unique<Grid>(std::move(squares), width);
    }

    Grid(std::vector<char> squares, int width);

    [[nodiscard]] std::optional<char> get_square(int x, int y) const;
    [[nodiscard]] std::optional<char> get_square(const Point &point) const;
    [[nodiscard]] char get_square_unsafe(int x, int y) const;
    [[nodiscard]] char get_square_unsafe(const Point &point) const;
    [[nodiscard]] int get_width() const;
    [[nodiscard]] int get_height() const;
    [[nodiscard]] std::unique_ptr<Grid> with_mutation(int x, int y,
                                                      char new_value);
    std::vector<std::optional<Point>>
    get_optional_adjacent_points(Point point) const;
    std::vector<Point> get_adjacent_points(Point point) const;

    struct Iterator {
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::vector<char>::iterator::difference_type;
        using value_type = char;

        Iterator();
        explicit Iterator(std::vector<char>::iterator vec_iterator);

        char operator*() const;

        Iterator &operator++();
        // NOLINTNEXTLINE(cert-dcl21-cpp)
        Iterator operator++(int);

        friend bool operator==(const Iterator &a, const Iterator &b);
        friend bool operator!=(const Iterator &a, const Iterator &b);

        friend difference_type operator-(const Iterator &a, const Iterator &b);

      private:
        std::vector<char>::iterator vec_iterator;
    };

    static_assert(std::input_iterator<Iterator>);

    Iterator begin();
    Iterator end();
    Point get_point(const Iterator &iterator);

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

    bool operator==(const Point &other) const;
};

enum class Direction { North, East, South, West };

Point operator+(const Point &point, const Vector &vector);
Point operator-(const Point &point, const Vector &vector);
Vector operator-(const Point &a, const Point &b);
Vector operator/(const Vector &a, int b);
Vector operator*(const Vector &a, int b);
std::ostream &operator<<(std::ostream &stream, const Point &point);
std::ostream &operator<<(std::ostream &stream, const Vector &vector);

std::unique_ptr<Grid> parse_grid(std::ifstream &input);

} // namespace aoc

namespace std {
template <> struct hash<aoc::Point> {
    size_t operator()(const aoc::Point &p) const;
};
} // namespace std

#endif // AOC_2024_GRID_H