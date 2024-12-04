#include "day3.h"
#include "gtest/gtest.h"
#include <fstream>

using namespace day3;

TEST(part1, example) {
    std::ifstream input_stream("example.txt");

    if (input_stream.fail()) {
        std::cerr << "Failed to load file!\n";
        exit(1);
    }

    ParsedInput parsed = parse_input(input_stream);
    int result = part1(parsed);

    std::cout << result << "\n";
}

TEST(part1, real) {
    std::ifstream input_stream("input.txt");

    if (input_stream.fail()) {
        std::cerr << "Failed to load file!\n";
        exit(1);
    }

    ParsedInput parsed = parse_input(input_stream);
    int result = part1(parsed);

    std::cout << result << "\n";
}

TEST(part2, example) {
    std::ifstream input_stream("example2.txt");

    if (input_stream.fail()) {
        std::cerr << "Failed to load file!\n";
        exit(1);
    }

    ParsedInput parsed = parse_input(input_stream);
    int result = part2(parsed);

    std::cout << result << "\n";
}

TEST(part2, real) {
    std::ifstream input_stream("input.txt");

    if (input_stream.fail()) {
        std::cerr << "Failed to load file!\n";
        exit(1);
    }

    ParsedInput parsed = parse_input(input_stream);
    int result = part2(parsed);

    std::cout << result << "\n";
}