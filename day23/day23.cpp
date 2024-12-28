#include "day23.h"

#include "../lib/assert.h"

#include <algorithm>
#include <fstream>
#include <memory>
#include <numeric>
#include <ranges>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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

        first_computer->connections.emplace_back(second_computer_it->second);
        second_computer->connections.emplace_back(first_computer_it->second);
    }

    return computers;
}

struct KosarajuContext {
    std::deque<std::weak_ptr<Computer>> vertex_list;
    std::unordered_set<std::string> visited_computers;
    std::unordered_set<std::string> assigned_computers;
    std::unordered_map<std::string, std::vector<std::string>> components;
};

// NOLINTNEXTLINE(misc-no-recursion)
void visit(const std::shared_ptr<Computer> &computer,
           KosarajuContext &context) {
    if (context.visited_computers.contains(computer->name)) {
        return;
    }

    context.visited_computers.insert(computer->name);

    for (const auto &connection : computer->connections) {
        auto connection_lock = connection.lock();
        aoc_assert(connection_lock, "unable to acquire connection ptr");
        visit(connection_lock, context);

        context.vertex_list.push_front(connection);
    }
}

// NOLINTNEXTLINE(misc-no-recursion)
void assign(const std::shared_ptr<Computer> &computer,
            const std::shared_ptr<Computer> &root, KosarajuContext &context) {
    if (context.assigned_computers.contains(computer->name)) {
        return;
    }

    context.assigned_computers.insert(computer->name);
    auto component_it = context.components.find(computer->name);
    if (component_it == context.components.end()) {
        auto insert_result =
            context.components.emplace(root->name, std::vector<std::string>());
        component_it = insert_result.first;
    }

    component_it->second.push_back(computer->name);

    for (const auto &connection : computer->connections) {
        auto connection_lock = connection.lock();
        aoc_assert(connection_lock, "unable to acquire connection ptr");
        assign(connection_lock, root, context);
    }
}

std::unordered_map<std::string, std::vector<std::string>>
get_connected_components(
    const std::unordered_map<std::string, std::shared_ptr<Computer>>
        &computers) {

    /* https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm */

    KosarajuContext context;

    for (const auto &computer : std::ranges::views::values(computers)) {
        visit(computer, context);
    }

    for (const auto &vertex : context.vertex_list) {
        auto vertex_lock = vertex.lock();
        aoc_assert(vertex_lock, "unable to acquire vertex ptr");

        assign(vertex_lock, vertex_lock, context);
    }

    return context.components;
}

int part1(const ParsedInput &input) {
    auto map = populate_connections(input);
    auto components = get_connected_components(map);

    return std::accumulate(
        components.begin(), components.end(), 0, [](int acc, auto pair) {
            auto has_3_computers = pair.second.size() == 3;
            auto has_t_computer =
                std::any_of(pair.second.begin(), pair.second.end(),
                            [](const std::string &computer) {
                                return computer.starts_with("t");
                            });

            if (has_3_computers && has_t_computer) {
                return acc + 1;
            }

            return acc;
        });
}

} // namespace day23
