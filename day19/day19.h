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
    std::string substring;

    Node(int index, std::string substring)
        : index(index), substring(std::move(substring)) {}
};

inline bool operator==(const Node &a, const Node &b) {
    return a.substring == b.substring && a.index == b.index;
}

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);

} // namespace day19

namespace std {
template <> struct hash<day19::Node> {
    std::size_t operator()(const day19::Node &node) const noexcept {
        size_t seed = 0;
        aoc::hash_combine(seed, node.index);
        aoc::hash_combine(seed, node.substring);
        return seed;
    }
};
} // namespace std

#endif // AOC2024_DAY19_H
