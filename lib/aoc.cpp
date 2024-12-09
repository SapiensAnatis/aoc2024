//
// Created by jay on 03/12/24.
//

#include "aoc.h"
#include <charconv>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <string>

namespace aoc {

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

    int offset = y * this->width;
    int index = offset + x;

    if (index < 0 || index >= static_cast<int>(this->squares.size())) {
        return std::nullopt;
    }

    return this->squares[offset + x];
}

std::ifstream get_ifstream(const std::string &filename) {
    std::ifstream stream(filename); // copied by CMake

    if (stream.fail()) {
        std::filesystem::path error_path =
            std::filesystem::current_path() / filename;
        std::cerr << "Failed to open file: " << error_path.string() << "\n";
        exit(1);
    }

    return stream;
}

std::ifstream get_example_ifstream() { return get_ifstream("example.txt"); }

std::ifstream get_example_ifstream(int example_num) {
    std::stringstream ss;
    ss << "example";
    ss << std::to_string(example_num);
    ss << ".txt";

    return get_ifstream(ss.str());
}

std::ifstream get_real_ifstream() { return get_ifstream("input.txt"); }

std::optional<int> stoi(const std::string_view &input) {
    int out;
    const std::from_chars_result result =
        std::from_chars(input.data(), input.data() + input.size(), out);

    if (result.ec == std::errc::invalid_argument ||
        result.ec == std::errc::result_out_of_range) {
        return std::nullopt;
    }

    return out;
}

std::vector<std::string_view> split(const std::string &str, char separator) {
    std::vector<std::string_view> results;

    auto split = std::ranges::views::split(str, separator);
    auto transform = std::ranges::views::transform(
        split, [](auto &&range) -> std::string_view {
            return std::string_view(range.begin(), range.end());
        });

    return {transform.begin(), transform.end()};
}
} // namespace aoc