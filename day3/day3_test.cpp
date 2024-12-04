#include "day3.h"
#include "gtest/gtest.h"
#include <fstream>

using namespace day3;

TEST(part1, example) {
    std::ifstream inputStream("example.txt");

    if (inputStream.fail()) {
        std::cerr << "Failed to load file!\n";
        exit(1);
    }

    ParsedInput parsed = parse_input(inputStream);
    int result = part1(parsed);

    std::cout << result << "\n";
}

TEST(part1, real) {
    std::ifstream inputStream("input.txt");

    if (inputStream.fail()) {
        std::cerr << "Failed to load file!\n";
        exit(1);
    }

    ParsedInput parsed = parse_input(inputStream);
    int result = part1(parsed);

    std::cout << result << "\n";
}

TEST(part2, example) {
    std::ifstream inputStream("example2.txt");

    if (inputStream.fail()) {
        std::cerr << "Failed to load file!\n";
        exit(1);
    }

    ParsedInput parsed = parse_input(inputStream);
    int result = part2(parsed);

    std::cout << result << "\n";
}

TEST(part2, real) {
    std::ifstream inputStream("input.txt");

    if (inputStream.fail()) {
        std::cerr << "Failed to load file!\n";
        exit(1);
    }

    ParsedInput parsed = parse_input(inputStream);
    int result = part2(parsed);

    std::cout << result << "\n";
}