#ifndef AOC2024_DAY21_H
#define AOC2024_DAY21_H
#include <array>
#include <fstream>
#include <vector>

namespace day21 {

struct ParsedInput {
    std::vector<std::string> codes;
};

ParsedInput parse_input(std::ifstream &input_stream);

long part1(const ParsedInput &input);

} // namespace day21

#endif // AOC2024_DAY21_H
