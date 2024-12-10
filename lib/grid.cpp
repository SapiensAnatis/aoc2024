#include "grid.h"
#include <algorithm>
#include <cassert>
#include <fstream>

namespace aoc {

Point::Point(int x, int y) : x(x), y(y) {}

bool Point::operator==(const Point &other) const {
    return other.x == this->x && other.y == this->y;
}

std::ostream &operator<<(std::ostream &stream, const Point &point) {
    return stream << "(" << point.x << ", " << point.y << ")";
}

Grid::Grid(std::vector<char> squares, int width)
    : width(width), squares(std::move(squares)) {
    this->height = static_cast<int>(this->squares.size()) / this->width;
}

int Grid::get_width() const { return this->width; }

int Grid::get_height() const { return this->height; }

std::optional<char> Grid::get_square(int x, int y) const {
    if (x < 0 || x >= this->width) {
        return std::nullopt;
    }

    if (y < 0 || y >= this->height) {
        return std::nullopt;
    }

    int index = this->calculate_array_index(x, y);

    assert((index >= 0 || index < static_cast<int>(this->squares.size())) &&
           "Grid bounds check failure");

    return this->squares[index];
}

std::optional<char> Grid::get_square(const Point &point) const {
    return this->get_square(point.x, point.y);
}

std::optional<Point> Grid::find_character(char to_find) const {
    auto it = std::find(this->squares.begin(), this->squares.end(), to_find);
    if (it == this->squares.end()) {
        return std::nullopt;
    }

    int index = static_cast<int>(it - this->squares.begin());
    int y = index / this->width;
    int x = index % this->width;

    return Point(x, y);
}

std::unique_ptr<Grid> Grid::with_mutation(int x, int y, char new_value) {
    auto new_vec = this->squares;
    new_vec[calculate_array_index(x, y)] = new_value;
    return std::make_unique<Grid>(new_vec, this->width);
}

int Grid::calculate_array_index(int x, int y) const {
    int offset = y * this->width;
    int index = offset + x;
    return index;
}

Point operator+(const Point &point, const Vector &vector) {
    return {point.x + vector.dx, point.y + vector.dy};
}

std::unique_ptr<Grid> parse_grid(std::ifstream &input) {
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

    return Grid::create(std::move(grid), width);
}

} // namespace aoc

namespace std {
size_t hash<aoc::Point>::operator()(const aoc::Point &p) const {
    size_t h1 = hash<int>()(p.x);
    size_t h2 = hash<int>()(p.y);

    return h1 ^ (h2 << 1);
}
} // namespace std