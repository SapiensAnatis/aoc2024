#ifndef AOC_2024_GRID_H
#define AOC_2024_GRID_H

#include <array>
#include <iterator>
#include <memory>
#include <optional>
#include <vector>

namespace aoc {

struct Point;

enum class Direction { North, East, South, West };

constexpr std::array<Direction, 4> directions = {Direction::North, Direction::East,
                                                 Direction::South, Direction::West};

std::ostream &operator<<(std::ostream &stream, Direction direction);

struct Vector {
    int dx;
    int dy;

    constexpr Vector(int dx, int dy) : dx(dx), dy(dy) {}
    constexpr explicit Vector(Direction direction) {
        switch (direction) {
        case Direction::North:
            this->dx = 0;
            this->dy = -1;
            break;
        case Direction::East:
            this->dx = 1;
            this->dy = 0;
            break;
        case Direction::South:
            this->dx = 0;
            this->dy = 1;
            break;
        case Direction::West:
            this->dx = -1;
            this->dy = 0;
            break;
        default:
            throw std::logic_error("Invalid direction!");
        }
    }

    Vector operator-() const;
};

constexpr std::array<Vector, 4> direction_vectors = {
    Vector(Direction::North), Vector(Direction::East), Vector(Direction::South),
    Vector(Direction::West)};

class Grid {
  public:
    static std::unique_ptr<Grid> create(std::vector<char> squares, int width);
    static std::unique_ptr<Grid> create(char fill, int width, int height);

    Grid(std::vector<char> squares, int width);

    [[nodiscard]] std::optional<char> get_square(int x, int y) const;
    [[nodiscard]] std::optional<char> get_square(Point point) const;
    [[nodiscard]] char get_square_unsafe(int x, int y) const;
    [[nodiscard]] char get_square_unsafe(Point point) const;
    [[nodiscard]] int get_width() const;
    [[nodiscard]] int get_height() const;
    [[nodiscard]] std::unique_ptr<Grid> with_mutation(int x, int y, char new_value);
    void set_square(int x, int y, char new_value);
    void set_square(Point point, char new_value);
    [[nodiscard]] std::vector<Point> get_adjacent_points(Point point) const;

    friend std::ostream &operator<<(std::ostream &stream, const Grid &grid);

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
    [[nodiscard]] std::vector<char>::size_type calculate_array_index(int x, int y) const;

    int width;
    int height;
    std::vector<char> squares;
};

struct Point {
    int x;
    int y;

    Point();
    Point(int x, int y);

    bool operator==(Point other) const;
};

Point operator+(Point point, Vector vector);
Point operator-(Point point, Vector vector);
Vector operator-(Point a, Point b);
Vector operator/(Vector a, int b);
Vector operator*(Vector a, int b);
bool operator==(Vector a, Vector b);
bool operator!=(Vector a, Vector b);
std::ostream &operator<<(std::ostream &stream, Point point);
std::ostream &operator<<(std::ostream &stream, const Grid &grid);

std::unique_ptr<Grid> parse_grid(std::istream &input);

} // namespace aoc

namespace std {

template <> struct hash<aoc::Point> {
    size_t operator()(aoc::Point p) const;
};

template <> struct hash<aoc::Vector> {
    size_t operator()(aoc::Vector v) const;
};

} // namespace std

#endif // AOC_2024_GRID_H