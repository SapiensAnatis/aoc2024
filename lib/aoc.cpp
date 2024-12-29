//
// Created by jay on 03/12/24.
//

#include "aoc.h"
#include <cassert>
#include <charconv>
#include <filesystem>
#include <iostream>
#include <optional>
#include <ranges>
#include <string>

namespace aoc {

std::ifstream get_ifstream(const std::string &filename) {
    std::ifstream stream(filename); // copied by CMake

    if (stream.fail()) {
        std::filesystem::path error_path = std::filesystem::current_path() / filename;
        std::cerr << "Failed to open file: " << error_path.string() << std::endl;
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

template <typename TNumber> TNumber parse(const std::string_view &input) {
    TNumber out;
    const std::from_chars_result result =
        std::from_chars(input.data(), input.data() + input.size(), out);

    if (result.ec == std::errc::invalid_argument || result.ec == std::errc::result_out_of_range) {
        throw std::runtime_error("Failed to parse number");
    }

    return out;
}

template <typename TNumber> std::optional<TNumber> try_parse(const std::string_view &input) {
    TNumber out;
    const std::from_chars_result result =
        std::from_chars(input.data(), input.data() + input.size(), out);

    if (result.ec == std::errc::invalid_argument || result.ec == std::errc::result_out_of_range) {
        return std::nullopt;
    }

    return out;
}

int parse_int(const std::string_view &input) { return parse<int>(input); }

std::optional<int> try_parse_int(const std::string_view &input) { return try_parse<int>(input); }

std::optional<long> try_parse_long(const std::string_view &input) { return try_parse<long>(input); }

std::optional<long long> try_parse_long_long(const std::string_view &input) {
    return try_parse<long long>(input);
}

std::optional<int> ctoi(char c) {
    if (c < '0' || c > '9') {
        return std::nullopt;
    }

    return c - '0';
}

std::vector<std::string_view> split(const std::string_view &str, char separator) {
    std::vector<std::string_view> results;

    auto split = std::ranges::views::split(str, separator);
    auto transform = std::ranges::views::transform(split, [](auto &&range) -> std::string_view {
        return std::string_view(range.begin(), range.end());
    });
    auto filter = std::ranges::views::filter(transform, [](auto &&r) { return r.length() > 0; });

    return {filter.begin(), filter.end()};
}

std::vector<std::string_view> split(const std::string &str, char separator) {
    return split(std::string_view(str), separator);
}

} // namespace aoc