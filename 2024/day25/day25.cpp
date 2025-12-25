#include "day25.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>

namespace day25 {

struct LockKeyHolder {
    std::vector<Lock> &locks;
    std::vector<Key> &keys;

    LockKeyHolder(std::vector<Lock> &locks, std::vector<Key> &keys) : locks(locks), keys(keys) {}

    void operator()(const Lock &lock) const { locks.push_back(lock); }
    void operator()(const Key &key) const { keys.push_back(key); }
};

std::variant<Lock, Key> parse_schematic(const std::string &schematic) {
    std::unordered_map<int, int> heights;
    std::stringstream ss(schematic);
    std::string line;
    bool is_lock = false;

    std::getline(ss, line);
    if (std::ranges::all_of(line, [](char c) { return c == '#'; })) {
        is_lock = true;
    }

    for (int col_num = 0; col_num < static_cast<int>(line.size()); col_num++) {
        heights[col_num] = 0;
    }

    while (std::getline(ss, line)) {
        for (int col_num = 0; col_num < static_cast<int>(line.size()); col_num++) {
            if (line[col_num] == '#') {
                heights[col_num]++;
            }
        }
    }

    if (is_lock) {
        return Lock(heights.at(0), heights.at(1), heights.at(2), heights.at(3), heights.at(4));
    }

    // For keys, we are mistakenly counting the last line which does not contribute; it's easier to
    // just subtract 1 across the board than fix the iteration
    return Key(heights.at(0) - 1, heights.at(1) - 1, heights.at(2) - 1, heights.at(3) - 1,
               heights.at(4) - 1);
}

ParsedInput parse_input(std::ifstream &input) {
    std::string line;
    std::vector<Lock> locks;
    std::vector<Key> keys;

    auto holder = LockKeyHolder(locks, keys);

    while (!input.eof()) {
        std::stringstream ss;
        while (std::getline(input, line) && !line.empty()) {
            ss << line << '\n';
        }

        std::string schematic = ss.str();

        auto lock_or_key = parse_schematic(schematic);
        std::visit(holder, lock_or_key);
    }

    return {.locks = locks, .keys = keys};
}

int part1(const ParsedInput &input) {
    int fit_count = 0;

    for (const auto &key : input.keys) {
        for (const auto &lock : input.locks) {
            bool fits = key.pin1 + lock.pin1 <= 5;
            fits &= key.pin2 + lock.pin2 <= 5;
            fits &= key.pin3 + lock.pin3 <= 5;
            fits &= key.pin4 + lock.pin4 <= 5;
            fits &= key.pin5 + lock.pin5 <= 5;

            if (fits) {
                fit_count++;
            }
        }
    }

    return fit_count;
}

} // namespace day25
