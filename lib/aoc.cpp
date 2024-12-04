//
// Created by jay on 03/12/24.
//

#include "aoc.h"
#include <string>
#include <iostream>
#include <filesystem>

namespace aoc {
    std::ifstream get_ifstream(bool example) {
        std::string filename = example ? "example.txt" : "input.txt";
        std::ifstream stream(filename); // copied by CMake

        if (stream.fail()) {
            std::cerr << "Failed to open file: " << std::filesystem::current_path() << "/" << filename << "\n";
            exit(1);
        }

        return stream;
    }

    std::ifstream get_example_ifstream() {
        return get_ifstream(true);
    }

    std::ifstream get_real_ifstream() {
        return get_ifstream(false);
    }
}