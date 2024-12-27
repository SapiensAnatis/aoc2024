#include "day22.h"

#include "../lib/aoc.h"

#include <iostream>

namespace day22 {

ParsedInput parse_input(std::ifstream &input) {
    std::string line;
    std::vector<secret_number> numbers{};

    while (std::getline(input, line)) {
        numbers.push_back(aoc::parse_int(line));
    }

    return {.initial_numbers = numbers};
}

secret_number mix_number(secret_number a, secret_number b) { return a ^ b; }

secret_number prune_number(secret_number a) { return a % 16777216; }

secret_number advance_number_once(secret_number number) {
    secret_number result = mix_number(number, number * 64);
    result = prune_number(result);
    result = mix_number(result, result / 32);
    result = prune_number(result);
    result = mix_number(result, result * 2048);
    result = prune_number(result);
    return result;
}

secret_number advance_number(secret_number number, int iterations) {
    secret_number result = number;

    for (int i = 0; i < iterations; i++) {
        result = advance_number_once(result);
    }

    return result;
}

secret_number part1(const ParsedInput &input) {
    secret_number result = 0;

    for (auto number : input.initial_numbers) {
        auto advanced = advance_number(number, 2000);
        std::cout << number << ": " << advanced << std::endl;
        result += advanced;
    }

    return result;
}

} // namespace day22
