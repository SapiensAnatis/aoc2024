//
// Created by jay on 29/12/24.
//
#include "../day01/day01.h"
#include "../day02/day02.h"
#include "../lib/aoc.h"
#include "gtest/gtest.h"
#include <chrono>

#define EXECUTE_DAY(DAY_NO)                                                                        \
    {                                                                                              \
        auto t1 = std::chrono::high_resolution_clock::now();                                       \
                                                                                                   \
        auto input_stream = aoc::get_example_ifstream(aoc::Day##DAY_NO);                           \
        const auto input = day##DAY_NO ::parse_input(input_stream);                                \
        auto t2 = std::chrono::high_resolution_clock::now();                                       \
                                                                                                   \
        std::cout << "Parsed day " << #DAY_NO << " input in "                                      \
                  << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1) << std::endl;  \
                                                                                                   \
        day##DAY_NO::part1(input);                                                                 \
        auto t3 = std::chrono::high_resolution_clock::now();                                       \
                                                                                                   \
        std::cout << "Ran day " << #DAY_NO << " part 1 in "                                        \
                  << std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2) << std::endl;  \
                                                                                                   \
        day##DAY_NO::part2(input);                                                                 \
        auto t4 = std::chrono::high_resolution_clock::now();                                       \
                                                                                                   \
        std::cout << "Ran day " << #DAY_NO << " part 2 in "                                        \
                  << std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3) << std::endl   \
                  << std::endl;                                                                    \
    }

TEST(perf, under_1_second) {
    auto t0 = std::chrono::high_resolution_clock::now();

    EXECUTE_DAY(01)
    EXECUTE_DAY(02)

    auto t_final = std::chrono::high_resolution_clock::now();

    std::cout << "Executed all days in "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t_final - t0) << std::endl;
}