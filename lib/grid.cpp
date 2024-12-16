#include "grid.h"
#include <algorithm>
#include <cassert>
#include <fstream>

namespace aoc {

Point::Point(int x, int y) : x(x), y(y) {}

Vector::Vector(int dx, int dy) : dx(dx), dy(dy) {}

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

    return get_square_unsafe(x, y);
}

std::optional<char> Grid::get_square(const Point &point) const {
    return this->get_square(point.x, point.y);
}

char Grid::get_square_unsafe(int x, int y) const {
    int index = this->calculate_array_index(x, y);

    assert((index >= 0 || index < static_cast<int>(this->squares.size())) &&
           "Grid bounds check failure");

    return this->squares[index];
}

char Grid::get_square_unsafe(const Point &point) const {
    return this->get_square_unsafe(point.x, point.y);
}

std::unique_ptr<Grid> Grid::with_mutation(int x, int y, char new_value) {
    auto new_vec = this->squares;
    new_vec[calculate_array_index(x, y)] = new_value;
    return std::make_unique<Grid>(new_vec, this->width);
}

std::vector<Point> Grid::get_adjacent_points(Point point) const {
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

std::vector<std::optional<Point>>
Grid::get_optional_adjacent_points(Point point) const {
    Point north = {point.x, point.y - 1};
    Point east = {point.x + 1, point.y};
    Point south = {point.x, point.y + 1};
    Point west = {point.x - 1, point.y};

    std::vector<std::optional<Point>> vec = {std::nullopt, std::nullopt,
                                             std::nullopt, std::nullopt};

    if (this->get_square(north)) {
        vec[0] = north;
    }
    if (this->get_square(east)) {
        vec[1] = east;
    }
    if (this->get_square(south)) {
        vec[2] = south;
    }
    if (this->get_square(west)) {
        vec[3] = west;
    }

    return vec;
}

int Grid::calculate_array_index(int x, int y) const {
    int offset = y * this->width;
    int index = offset + x;
    return index;
}

Grid::Iterator Grid::begin() { return Grid::Iterator(this->squares.begin()); }

Grid::Iterator Grid::end() { return Grid::Iterator(this->squares.end()); }

Point Grid::get_point(const Grid::Iterator &it) {
    auto index = static_cast<int>(it - this->begin());
    int x = index % this->width;
    int y = index / this->width;

    return {x, y};
}

Grid::Iterator::Iterator(std::vector<char>::iterator vec_iterator)
    : vec_iterator(vec_iterator) {}

Grid::Iterator::Iterator() = default;

char Grid::Iterator::operator*() const { return *this->vec_iterator; }

Grid::Iterator &Grid::Iterator::operator++() {
    this->vec_iterator++;
    return *this;
}

Grid::Iterator::difference_type operator-(const Grid::Iterator &a,
                                          const Grid::Iterator &b) {
    return a.vec_iterator - b.vec_iterator;
}

// NOLINTNEXTLINE(cert-dcl21-cpp)
Grid::Iterator Grid::Iterator::operator++(int) {
    Grid::Iterator tmp = *this;
    ++(*this);
    return tmp;
}

bool operator==(const Grid::Iterator &a, const Grid::Iterator &b) {
    return a.vec_iterator == b.vec_iterator;
}

bool operator!=(const Grid::Iterator &a, const Grid::Iterator &b) {
    return a.vec_iterator != b.vec_iterator;
}

bool Point::operator==(const Point &other) const {
    return other.x == this->x && other.y == this->y;
}

std::ostream &operator<<(std::ostream &stream, const Point &point) {
    return stream << "(" << point.x << ", " << point.y << ")";
}

Point operator+(const Point &point, const Vector &vector) {
    return {point.x + vector.dx, point.y + vector.dy};
}

Point operator-(const Point &point, const Vector &vector) {
    return {point.x - vector.dx, point.y - vector.dy};
}

Vector operator-(const Point &a, const Point &b) {
    return {a.x - b.x, a.y - b.y};
}

Vector operator/(const Vector &a, int b) { return {a.dx / b, a.dy / b}; }

Vector operator*(const Vector &a, int b) { return {a.dx * b, a.dy * b}; }

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