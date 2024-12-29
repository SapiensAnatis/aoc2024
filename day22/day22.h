#ifndef AOC2024_DAY22_H
#define AOC2024_DAY22_H

#include "../lib/assert.h"
#include "../lib/hash.hpp"
#include <fstream>
#include <unordered_map>
#include <vector>

namespace day22 {

typedef unsigned long secret_number;

struct ParsedInput {
    std::vector<secret_number> initial_numbers;
};

template <class T>
concept Collection = requires(T a, int i) {
    { a[i] } -> std::convertible_to<int>;
    { a.size() } -> std::convertible_to<size_t>;
};

struct ChangeSequence {
    int change1, change2, change3, change4;

    template <Collection T> static ChangeSequence create(const T &collection) {
        aoc_assert(collection.size() == 4, "invalid collection size");

        return {
            .change1 = collection[0],
            .change2 = collection[1],
            .change3 = collection[2],
            .change4 = collection[3],
        };
    }
};

inline bool operator==(const ChangeSequence &lhs, const ChangeSequence &rhs) {
    return lhs.change1 == rhs.change1 && lhs.change2 == rhs.change2 && lhs.change3 == rhs.change3 &&
           lhs.change4 == rhs.change4;
}

inline std::ostream &operator<<(std::ostream &stream, const ChangeSequence &sequence) {
    return stream << sequence.change1 << "," << sequence.change2 << "," << sequence.change3 << ","
                  << sequence.change4;
}

ParsedInput parse_input(std::ifstream &input);

secret_number advance_number_once(secret_number number);

secret_number part1(const ParsedInput &input);

std::unordered_map<ChangeSequence, secret_number>
advance_number_and_track_changes(secret_number init_number, int iterations);

secret_number part2(const ParsedInput &input);

} // namespace day22

template <> struct std::hash<day22::ChangeSequence> {
    size_t operator()(const day22::ChangeSequence &seq) const noexcept {
        size_t seed = 0;
        aoc::hash_combine(seed, seq.change1);
        aoc::hash_combine(seed, seq.change2);
        aoc::hash_combine(seed, seq.change3);
        aoc::hash_combine(seed, seq.change4);
        return seed;
    }
};

#endif // AOC2024_DAY22_H
