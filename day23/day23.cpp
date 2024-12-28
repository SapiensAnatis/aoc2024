#include "day23.h"

#include "../lib/assert.h"
#include "../lib/hash.hpp"

#include <algorithm>
#include <fstream>
#include <memory>
#include <numeric>
#include <ranges>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace day23 {
struct ComputerTriplet {
    std::array<std::string, 3> computers;

    ComputerTriplet(std::string a, std::string b, std::string c)
        : computers({std::move(a), std::move(b), std::move(c)}) {}
};

bool operator==(ComputerTriplet lhs, ComputerTriplet rhs) {
    std::sort(lhs.computers.begin(), lhs.computers.end());
    std::sort(rhs.computers.begin(), rhs.computers.end());

    return lhs.computers == rhs.computers;
}

} // namespace day23

template <> struct std::hash<day23::ComputerTriplet> {
    size_t operator()(day23::ComputerTriplet a) const noexcept {
        std::sort(a.computers.begin(), a.computers.end());

        size_t seed = 0;
        aoc::hash_combine(seed, a.computers[0]);
        aoc::hash_combine(seed, a.computers[1]);
        aoc::hash_combine(seed, a.computers[2]);
        return seed;
    }
};

namespace day23 {

ParsedInput parse_input(std::ifstream &input) {
    std::string line;
    std::vector<std::pair<std::string, std::string>> connections;

    while (std::getline(input, line)) {
        std::string_view line_view(line);
        std::string first_computer(line_view.substr(0, 2));
        std::string second_computer(line_view.substr(3, 2));

        connections.emplace_back(first_computer, second_computer);
    }

    return {.connections = connections};
}

std::unordered_map<std::string, std::shared_ptr<Computer>>
populate_connections(const ParsedInput &input) {
    std::unordered_map<std::string, std::shared_ptr<Computer>> computers;
    computers.reserve(input.connections.size());

    for (const auto &connection : input.connections) {
        auto first_computer_it = computers.find(connection.first);
        auto second_computer_it = computers.find(connection.second);

        if (first_computer_it == computers.end()) {
            auto [it, _] = computers.emplace(
                connection.first, std::make_shared<Computer>(connection.first));
            first_computer_it = it;
        }

        if (second_computer_it == computers.end()) {
            auto [it, _] = computers.emplace(
                connection.second,
                std::make_shared<Computer>(connection.second));
            second_computer_it = it;
        }

        auto first_computer = first_computer_it->second;
        auto second_computer = second_computer_it->second;

        first_computer->add_connection(second_computer_it->second);
        second_computer->add_connection(first_computer_it->second);
    }

    return computers;
}

std::unordered_set<ComputerTriplet> get_connected_triplets(
    const std::unordered_map<std::string, std::shared_ptr<Computer>>
        &computers) {
    std::unordered_set<ComputerTriplet> components;
    std::unordered_set<std::string> checked_computers;

    for (const auto &first_computer : std::ranges::views::values(computers)) {
        for (const auto &second_computer_ref :
             first_computer->get_connections()) {
            auto second_computer = second_computer_ref.lock();
            aoc_assert(second_computer, "unable to acquire computer ptr");

            for (const auto &third_computer_ref :
                 second_computer->get_connections()) {
                auto third_computer = third_computer_ref.lock();
                aoc_assert(third_computer, "unable to acquire computer ptr");

                if (first_computer->is_connected_to(
                        third_computer->get_name())) {
                    components.emplace(first_computer->get_name(),
                                       second_computer->get_name(),
                                       third_computer->get_name());
                }
            }
        }
    }

    return components;
}

int part1(const ParsedInput &input) {
    auto map = populate_connections(input);
    auto components = get_connected_triplets(map);

    int acc = 0;
    for (const auto &component : components) {
        if (std::any_of(
                component.computers.begin(), component.computers.end(),
                [](const std::string &c) { return c.starts_with('t'); })) {
            acc += 1;
        }
    }

    return acc;
}

} // namespace day23
