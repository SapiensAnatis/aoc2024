#ifndef AOC2024_DAY23_H
#define AOC2024_DAY23_H

#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace day23 {

struct Computer {
    std::string name;
    std::vector<std::weak_ptr<Computer>> connections{};

    explicit Computer(std::string name) : name(std::move(name)) {}
    explicit Computer(std::string_view name) : Computer(std::string(name)) {}
};

struct ParsedInput {
    std::vector<std::pair<std::string, std::string>> connections;
    std::unordered_map<std::string, std::shared_ptr<Computer>> computers;
};

ParsedInput parse_input(std::ifstream &input);

void populate_connections(ParsedInput &input);

int part1(const ParsedInput &input);

} // namespace day23

#endif // AOC2024_DAY23_H
