#ifndef AOC2024_DAY19_H
#define AOC2024_DAY19_H
#include <string>
#include <unordered_set>
#include <vector>

namespace day19 {

struct ParsedInput {
    std::unordered_set<std::string> towels;
    std::vector<std::string> patterns;
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input);

int part2(const ParsedInput &input);

} // namespace day19

#endif // AOC2024_DAY19_H
