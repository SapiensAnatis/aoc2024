//
// Created by jay on 20/12/24.
//
#include "./assert.h"
#include <iostream>

namespace aoc {
void fail_assert(const std::string &message, const std::source_location &location) {

    std::cerr << location.file_name() << ':' << location.line() << ":" << location.column() << " "
              << location.function_name() << " - assertion failed: \"" << message << "\""
              << std::endl;

    abort();
}
} // namespace aoc