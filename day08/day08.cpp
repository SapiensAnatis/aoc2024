
#include "day08.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>

namespace day8 {

ParsedInput::ParsedInput(std::unique_ptr<aoc::Grid> grid)
    : grid(std::move(grid)) {}

ParsedInput parse_input(std::ifstream &input_stream) {
    auto grid = aoc::parse_grid(input_stream);
    return ParsedInput(std::move(grid));
}

int part1(const ParsedInput &input) {
    std::unordered_multimap<char, aoc::Point> antennae_map;
    std::unordered_set<char> antennae_names;
    std::unordered_set<aoc::Point> antinode_points;

    for (auto it = input.grid->begin(); it != input.grid->end(); it++) {
        if (*it != '.') {
            antennae_map.emplace(*it, input.grid->get_point(it));
            antennae_names.insert(*it);
        }
    }

    for (auto antennae_name : antennae_names) {
        std::vector<aoc::Point> positions;
        for (auto [it, end] = antennae_map.equal_range(antennae_name);
             it != end; it++) {
            positions.push_back(it->second);
        }

        if (positions.size() < 2) {
            continue;
        }

        for (auto it_a = positions.begin(); it_a != positions.end(); it_a++) {
            for (auto it_b = positions.begin();
                 it_b != positions.end() && it_b != it_a; it_b++) {
                auto a_to_b_vec = *it_b - *it_a;
                auto b_to_a_vec = *it_a - *it_b;

                auto antinode_a = *it_a + (a_to_b_vec * 2);
                auto antinode_b = *it_b + (b_to_a_vec * 2);

                std::cout << "Pair: " << *it_a << " and " << *it_b << "\n";

                if (input.grid->get_square(antinode_a)) {
                    std::cout << "Antinode at: " << antinode_a << "\n";
                    antinode_points.insert(antinode_a);
                }

                if (input.grid->get_square(antinode_b)) {
                    std::cout << "Antinode at: " << antinode_b << "\n";
                    antinode_points.insert(antinode_b);
                }
            }
        }
    }

    return static_cast<int>(antinode_points.size());
}

int part2(const ParsedInput &input) {
    std::unordered_multimap<char, aoc::Point> antennae_map;
    std::unordered_set<char> antennae_names;
    std::unordered_set<aoc::Point> antinode_points;

    for (auto it = input.grid->begin(); it != input.grid->end(); it++) {
        if (*it != '.') {
            antennae_map.emplace(*it, input.grid->get_point(it));
            antennae_names.insert(*it);
        }
    }

    for (auto antennae_name : antennae_names) {
        std::vector<aoc::Point> positions;
        for (auto [it, end] = antennae_map.equal_range(antennae_name);
             it != end; it++) {
            positions.push_back(it->second);
        }

        if (positions.size() < 2) {
            continue;
        }

        for (auto it_a = positions.begin(); it_a != positions.end(); it_a++) {
            antinode_points.insert(*it_a);

            for (auto it_b = positions.begin();
                 it_b != positions.end() && it_b != it_a; it_b++) {
                auto a_to_b_vec = *it_b - *it_a;
                auto b_to_a_vec = *it_a - *it_b;

                auto antinode_a = *it_a + (a_to_b_vec * 2);
                auto antinode_b = *it_b + (b_to_a_vec * 2);

                std::cout << "Pair for " << antennae_name << ": " << *it_a
                          << " and " << *it_b << "\n";

                while (input.grid->get_square(antinode_a)) {
                    std::cout << "Antinode at: " << antinode_a << "\n";
                    antinode_points.insert(antinode_a);
                    antinode_a = antinode_a + a_to_b_vec;
                }

                while (input.grid->get_square(antinode_b)) {
                    std::cout << "Antinode at: " << antinode_b << "\n";
                    antinode_points.insert(antinode_b);
                    antinode_b = antinode_b + b_to_a_vec;
                }
            }
        }
    }

    return static_cast<int>(antinode_points.size());
}

} // namespace day8