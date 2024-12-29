//
// Created by jay on 20/12/24.
//

#ifndef AOC2024_ASSERT_H
#define AOC2024_ASSERT_H

#include <source_location>
#include <string>

#if NDEBUG
#define aoc_assert(condition, message)
#else
#define aoc_assert(condition, message)                                                             \
    ((static_cast<bool>(condition)) ? static_cast<void>(0) : aoc::fail_assert(message))
#endif

namespace aoc {

[[noreturn]] void
fail_assert(const std::string &message,
            const std::source_location &location = std::source_location::current());

} // namespace aoc

#endif // AOC2024_ASSERT_H
