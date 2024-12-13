#include "day11.h"
#include <fstream>
#include <sstream>
#include <string>

namespace day11 {

ParsedInput parse_input(std::ifstream &input_stream) {
    std::string line;
    std::getline(input_stream, line);
    std::vector<Stone> stones;

    std::stringstream ss(line);
    int stone_num;
    while (ss >> stone_num) {
        stones.emplace_back(stone_num);
    }

    return {stones};
}

int part1() {
    int num_blinks = 25;
    for (int i = 0; i < num_blinks; i++) {
        // todo
    }

    return 0;
}

} // namespace day11
