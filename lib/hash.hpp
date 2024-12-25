//
// Created by jay on 20/12/24.
//

#ifndef AOC2024_HASH_HPP
#define AOC2024_HASH_HPP

#include <functional>

namespace aoc {

// stolen from Boost / StackOverflow
// https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
template <typename T> void hash_combine(std::size_t &seed, const T &v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

} // namespace aoc

#endif // AOC2024_HASH_HPP
