#include "../lib/aoc.h"
#include "day23.h"

#include "gtest/gtest.h"
#include <algorithm>
#include <ranges>

TEST(day23_part1, example) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day23::parse_input(input_stream);

    day23::populate_connections(input);

    auto three_connected = std::count_if(
        input.computers.begin(), input.computers.end(),
        [](const auto &pair) { return pair.second->connections.size() == 3; });

    ASSERT_EQ(three_connected, 12);
}

TEST(day23_part1, real) {}

TEST(day23_part2, example) {}

TEST(day23_part2, real) {}
