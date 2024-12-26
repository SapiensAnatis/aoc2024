#ifndef AOC2024_DAY19_H
#define AOC2024_DAY19_H
#include "../lib/hash.hpp"
#include <string>
#include <unordered_set>
#include <vector>

namespace day19 {

struct ParsedInput {
    std::unordered_set<std::string> towels;
    std::vector<std::string> patterns;
};

struct Node {
    int index;
    std::vector<std::string> path;

    Node(int index, std::vector<std::string> path)
        : index(index), path(std::move(path)) {}
};

inline bool operator==(const Node &a, const Node &b) {
    return a.path == b.path && a.index == b.index;
}

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);

long long part2(const ParsedInput &input);

} // namespace day19

namespace std {

template <> struct hash<day19::Node> {
    std::size_t operator()(const day19::Node &node) const noexcept {
        size_t seed = 0;
        aoc::hash_combine(seed, node.index);

        for (auto &path_part : node.path) {
            aoc::hash_combine(seed, path_part);
        }

        return seed;
    }
};

} // namespace std

#endif // AOC2024_DAY19_H
