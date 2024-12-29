#ifndef AOC2024_DAY23_H
#define AOC2024_DAY23_H

#include <fstream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace day23 {

class Computer {
  public:
    explicit Computer(std::string name) : name(std::move(name)) {}
    explicit Computer(std::string_view name) : Computer(std::string(name)) {}

    [[nodiscard]] std::string get_name() const { return this->name; }
    [[nodiscard]] const std::vector<std::weak_ptr<Computer>> &get_connections() const {
        return this->connections;
    }
    [[nodiscard]] std::unordered_set<std::string> get_connection_names() const {
        return this->connection_names;
    }
    void add_connection(const std::shared_ptr<Computer> &connection) {
        this->connections.push_back(std::weak_ptr((connection)));
        this->connection_names.insert(connection->get_name());
    }
    [[nodiscard]] bool is_connected_to(const std::string &other_computer_name) const {
        return this->connection_names.contains(other_computer_name);
    }

  private:
    std::string name;
    std::vector<std::weak_ptr<Computer>> connections{};
    std::unordered_set<std::string> connection_names{};
};

struct ParsedInput {
    std::vector<std::pair<std::string, std::string>> connections;
};

ParsedInput parse_input(std::ifstream &input);

int part1(const ParsedInput &input);

std::string part2(const ParsedInput &input);

} // namespace day23

#endif // AOC2024_DAY23_H
