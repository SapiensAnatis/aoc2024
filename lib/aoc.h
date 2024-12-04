//
// Created by jay on 03/12/24.
//

#ifndef AOC2024_AOC_H
#define AOC2024_AOC_H

#include <fstream>

namespace aoc {
    std::ifstream get_example_ifstream();

    std::ifstream get_example_ifstream(int example_num);

    std::ifstream get_real_ifstream();
}

#endif //AOC2024_AOC_H
