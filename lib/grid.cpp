#include "grid.h"
#include "./assert.h"
#include "hash.hpp"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <stdexcept>

namespace aoc {

std::ostream &operator<<(std::ostream &stream, Direction direction) {
    std::string text;

    switch (direction) {
    case Direction::North:
        text = "North";
        break;
    case Direction::East:
        text = "East";
        break;
    case Direction::South:
        text = "South";
        break;
    case Direction::West:
        text = "West";
        break;
    }

    return stream << text;
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

Grid::Iterator Grid::begin() { return Grid::Iterator(this->squares.begin()); }

Grid::Iterator Grid::end() { return Grid::Iterator(this->squares.end()); }

Point Grid::get_point(const Grid::Iterator &it) {
    auto index = static_cast<int>(it - this->begin());
    int x = index % this->width;
    int y = index / this->width;

    return {x, y};
}

Grid::Iterator::Iterator(std::vector<char>::iterator vec_iterator) : vec_iterator(vec_iterator) {}

Grid::Iterator::Iterator() = default;

char Grid::Iterator::operator*() const { return *this->vec_iterator; }

Grid::Iterator &Grid::Iterator::operator++() {
    this->vec_iterator++;
    return *this;
}

Grid::Iterator::difference_type operator-(const Grid::Iterator &a, const Grid::Iterator &b) {
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

std::ostream &operator<<(std::ostream &stream, Point point) {
    return stream << "(" << point.x << ", " << point.y << ")";
}

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
