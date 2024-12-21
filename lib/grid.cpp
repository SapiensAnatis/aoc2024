#include "grid.h"
#include "./assert.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>

namespace aoc {

Point::Point(int x, int y) : x(x), y(y) {}

Vector::Vector(int dx, int dy) : dx(dx), dy(dy) {}

Vector::Vector(Direction direction) {
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

Vector Vector::operator-() const { return {-this->dx, -this->dy}; }

std::unique_ptr<Grid> Grid::create(std::vector<char> squares, int width) {
    return std::make_unique<Grid>(std::move(squares), width);
}

std::unique_ptr<Grid> Grid::create(char fill, int width, int height) {
    std::vector<char> squares(width * height, fill);
    return Grid::create(squares, width);
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

    return get_square_unsafe(x, y);
}

std::optional<char> Grid::get_square(Point point) const {
    return this->get_square(point.x, point.y);
}

char Grid::get_square_unsafe(int x, int y) const {
    auto index = this->calculate_array_index(x, y);

    assert((index >= 0 || index < this->squares.size()) &&
           "Grid bounds check failure");

    return this->squares[index];
}

char Grid::get_square_unsafe(Point point) const {
    return this->get_square_unsafe(point.x, point.y);
}

std::unique_ptr<Grid> Grid::with_mutation(int x, int y, char new_value) {
    auto new_vec = this->squares;
    new_vec[calculate_array_index(x, y)] = new_value;
    return std::make_unique<Grid>(new_vec, this->width);
}

void Grid::set_square(int x, int y, char new_value) {
    auto index = this->calculate_array_index(x, y);
    aoc_assert(index > 0 && index < this->squares.size(),
               "Grid bounds check failure");

    this->squares[index] = new_value;
}

void Grid::set_square(Point point, char new_value) {
    auto index = this->calculate_array_index(point.x, point.y);
    aoc_assert(index > 0 && index < this->squares.size(),
               "Grid bounds check failure");

    this->squares[index] = new_value;
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

std::ostream &operator<<(std::ostream &stream, const Grid &grid) {
    std::string result;
    result.reserve(grid.squares.size() + grid.height);

    for (std::vector<char>::size_type i = 0; i < grid.squares.size(); i++) {
        result += grid.squares[i];
        if ((i + 1) % grid.width == 0) {
            result += "\n";
        }
    }

    return stream << result;
}

std::vector<char>::size_type Grid::calculate_array_index(int x, int y) const {
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

std::ostream &operator<<(std::ostream &stream, Point point) {
    return stream << "(" << point.x << ", " << point.y << ")";
}

Point operator+(Point point, Vector vector) {
    return {point.x + vector.dx, point.y + vector.dy};
}

Point operator-(Point point, Vector vector) {
    return {point.x - vector.dx, point.y - vector.dy};
}

Vector operator-(Point a, Point b) { return {a.x - b.x, a.y - b.y}; }

Vector operator/(Vector a, int b) { return {a.dx / b, a.dy / b}; }

Vector operator*(Vector a, int b) { return {a.dx * b, a.dy * b}; }

std::unique_ptr<Grid> parse_grid(std::istream &input) {
    std::vector<char> grid;
    std::string line;
    int width;

    std::getline(input, line);
    aoc_assert(!input.fail(), "Failed to read first line");
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