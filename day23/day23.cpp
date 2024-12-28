#include "day23.h"

#include <fstream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace day23 {

ParsedInput parse_input(std::ifstream &input) {
    std::string line;
    std::vector<std::pair<std::string, std::string>> connections;
    std::unordered_map<std::string, std::shared_ptr<Computer>> computers;

    while (std::getline(input, line)) {
        std::string_view line_view(line);
        std::string first_computer(line_view.substr(0, 2));
        std::string second_computer(line_view.substr(3, 2));

        connections.emplace_back(first_computer, second_computer);

        if (!computers.contains(first_computer)) {
            computers[first_computer] =
                std::make_shared<Computer>(first_computer);
        }

        if (!computers.contains(second_computer)) {
            computers[second_computer] =
                std::make_shared<Computer>(second_computer);
        }
    }

    return {.connections = connections, .computers = computers};
}

void populate_connections(ParsedInput &input) {
    for (const auto &connection : input.connections) {
        auto first_computer = input.computers.at(connection.first);
        auto second_computer = input.computers.at(connection.second);

        first_computer->connections.push_back(std::weak_ptr(second_computer));
        second_computer->connections.push_back(std::weak_ptr(first_computer));
    }
}

int part1(const ParsedInput &input) {
    for (const auto &connection : input.connections) {
        auto first_computer = input.computers.at(connection.first);
        auto second_computer = input.computers.at(connection.second);

        first_computer->connections.push_back(std::weak_ptr(second_computer));
        second_computer->connections.push_back(std::weak_ptr(first_computer));
    }

    return 0;
}

} // namespace day23
