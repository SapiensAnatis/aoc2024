#ifndef AOC2024_DAY22_H
#define AOC2024_DAY22_H

#include <fstream>
#include <vector>

namespace day22 {

typedef unsigned long secret_number;

struct ParsedInput {
    std::vector<secret_number> initial_numbers;
};

ParsedInput parse_input(std::ifstream &input);

secret_number advance_number_once(secret_number number);

secret_number advance_number(secret_number number, int iterations);

secret_number part1(const ParsedInput &input);

} // namespace day22

#endif // AOC2024_DAY22_H
