#ifndef AOC_2024_GRID_H
#define AOC_2024_GRID_H

#include "./assert.h"
#include "hash.hpp"

#include <array>
#include <iterator>
#include <memory>
#include <optional>
#include <vector>

namespace aoc {

struct Point {
    int x;
    int y;

    Point() : Point(0, 0) {}
    Point(int x, int y) : x(x), y(y) {}

    bool operator==(Point other) const { return other.x == this->x && other.y == this->y; }
};

enum class Direction { North, East, South, West };

constexpr std::array directions = {Direction::North, Direction::East, Direction::South,
                                   Direction::West};

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

    [[nodiscard]] int get_square_magnitude() const { return dx * dx + dy * dy; }

    [[nodiscard]] Vector rotate_90deg_clockwise() const {
        // Matrix multiplication with rotational matrix:
        // x' = x cos(pi / 2) - y sin(pi / 2) = -y
        // y' = x sin(pi / 2) + y cos(pi / 2) = x
        int new_x = -this->dy;
        int new_y = this->dx;

        return {new_x, new_y};
    }

    Vector operator-() const { return {-this->dx, -this->dy}; }
};

constexpr std::array<Vector, 4> direction_vectors = {
    Vector(Direction::North), Vector(Direction::East), Vector(Direction::South),
    Vector(Direction::West)};

class Grid {
  public:
    static std::unique_ptr<Grid> create(std::vector<char> squares, int width) {
        return std::make_unique<Grid>(std::move(squares), width);
    }

    static std::unique_ptr<Grid> create(char fill, int width, int height) {
        std::vector squares(width * height, fill);
        return create(squares, width);
    }

    Grid(std::vector<char> squares, int width) : width(width), squares(std::move(squares)) {
        this->height = static_cast<int>(this->squares.size()) / this->width;
    }

    [[nodiscard]] std::optional<char> get_square(Point point) const {
        return this->get_square(point.x, point.y);
    }

    [[nodiscard]] std::optional<char> get_square(int x, int y) const {
        if (x < 0 || x >= this->width) {
            return std::nullopt;
        }

        if (y < 0 || y >= this->height) {
            return std::nullopt;
        }

        return get_square_unsafe(x, y);
    }

    [[nodiscard]] char get_square_unsafe(Point point) const {
        return this->get_square_unsafe(point.x, point.y);
    }

    [[nodiscard]] char get_square_unsafe(int x, int y) const {
        auto index = this->calculate_array_index(x, y);

        return this->squares[index];
    }

    [[nodiscard]] int get_width() const { return this->width; }
    [[nodiscard]] int get_height() const { return this->height; }

    [[nodiscard]] std::unique_ptr<Grid> with_mutation(int x, int y, char new_value) {
        auto new_vec = this->squares;
        new_vec[calculate_array_index(x, y)] = new_value;
        return std::make_unique<Grid>(new_vec, this->width);
    }

    void set_square(Point point, char new_value) { this->set_square(point.x, point.y, new_value); }

    void set_square(int x, int y, char new_value) {
        auto index = this->calculate_array_index(x, y);
        aoc_assert(index > 0 && index < this->squares.size(), "Grid bounds check failure");

        this->squares[index] = new_value;
    }

    [[nodiscard]] std::vector<Point> get_adjacent_points(Point point) const {
        Point north = {point.x, point.y - 1};
        Point east = {point.x + 1, point.y};
        Point south = {point.x, point.y + 1};
        Point west = {point.x - 1, point.y};

        std::vector<Point> vec;

        if (this->get_square(north)) {
            vec.push_back(north);
        }
        if (this->get_square(east)) {
            vec.push_back(east);
        }
        if (this->get_square(south)) {
            vec.push_back(south);
        }
        if (this->get_square(west)) {
            vec.push_back(west);
        }

        return vec;
    }

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
    [[nodiscard]] std::vector<char>::size_type calculate_array_index(int x, int y) const {
        aoc_assert(x >= 0 && x < this->width && y >= 0 && y < this->height,
                   "grid bounds check failure");

        int offset = y * this->width;
        int index = offset + x;
        return index;
    }

    int width;
    int height;
    std::vector<char> squares;
};

inline Point operator+(Point point, Vector vector) {
    return {point.x + vector.dx, point.y + vector.dy};
}

inline Point operator-(Point point, Vector vector) {
    return {point.x - vector.dx, point.y - vector.dy};
}

inline Vector operator-(Point a, Point b) { return {a.x - b.x, a.y - b.y}; }

inline Vector operator/(Vector a, int b) { return {a.dx / b, a.dy / b}; }

inline Vector operator*(Vector a, int b) { return {a.dx * b, a.dy * b}; }

inline bool operator==(Vector a, Vector b) { return a.dx == b.dx && a.dy == b.dy; }

inline bool operator!=(Vector a, Vector b) { return !(a == b); }

std::ostream &operator<<(std::ostream &stream, Point point);
std::ostream &operator<<(std::ostream &stream, const Grid &grid);

std::unique_ptr<Grid> parse_grid(std::istream &input);

} // namespace aoc

namespace std {

template <> struct hash<aoc::Point> {
    size_t operator()(aoc::Point p) const noexcept {
        size_t seed = 0;

        aoc::hash_combine(seed, hash<int>()(p.x));
        aoc::hash_combine(seed, hash<int>()(p.y));

        return seed;
    }
};

template <> struct hash<aoc::Vector> {
    size_t operator()(aoc::Vector v) const noexcept {
        size_t seed = 0;

        aoc::hash_combine(seed, hash<int>()(v.dx));
        aoc::hash_combine(seed, hash<int>()(v.dy));

        return seed;
    }
};

} // namespace std

#endif // AOC_2024_GRID_H