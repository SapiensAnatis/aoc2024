//
// Created by jay on 03/12/24.
//

#include "aoc.h"
#include <string>
#include <iostream>
#include <filesystem>

namespace aoc {
    std::ifstream get_ifstream(const std::string &filename) {
        std::ifstream stream(filename); // copied by CMake

        if (stream.fail()) {
            std::filesystem::path error_path = std::filesystem::current_path() / filename;
            std::cerr << "Failed to open file: " << error_path.string() << "\n";
            exit(1);
        }

        return stream;
    }

    std::ifstream get_example_ifstream() {
        return get_ifstream("example.txt");
    }

    std::ifstream get_example_ifstream(int example_num) {
        std::stringstream ss;
        ss << "example";
        ss << std::to_string(example_num);
        ss << ".txt";

        return get_ifstream(ss.str());
    }

    std::ifstream get_real_ifstream() {
        return get_ifstream("input.txt");
    }
}