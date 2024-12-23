#include "day15.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace day15 {

ParsedInput parse_input(std::ifstream &input_stream) {
    std::stringstream grid;
    std::stringstream moves;

    std::string line;
    while (std::getline(input_stream, line) && !line.empty()) {
        grid << line << std::endl;
    }

    auto parsed_grid = aoc::parse_grid(grid);

    std::vector<aoc::Direction> parsed_moves;

    while (!input_stream.eof()) {
        char c;
        input_stream.get(c);

        switch (c) {
        case '^':
            parsed_moves.push_back(aoc::Direction::North);
            break;
        case '>':
            parsed_moves.push_back(aoc::Direction::East);
            break;
        case 'v':
            parsed_moves.push_back(aoc::Direction::South);
            break;
        case '<':
            parsed_moves.push_back(aoc::Direction::West);
            break;
        case '\n':
            break;
        default:
            std::cerr << "Invalid character in input: '" << c << "'"
                      << std::endl;
            exit(1);
        }
    }

    return {std::move(parsed_grid), parsed_moves};
}

} // namespace day15
