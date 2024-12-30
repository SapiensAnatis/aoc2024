//
// Created by jay on 29/12/24.
//
#include "../day01/day01.h"
#include "../day02/day02.h"
#include "../day03/day03.h"
#include "../day04/day04.h"
#include "../day05/day05.h"
#include "../day06/day06.h"
#include "../day07/day07.h"
#include "../day08/day08.h"
#include "../day09/day09.h"
#include "../day10/day10.h"
#include "../day11/day11.h"
#include "../day12/day12.h"
#include "../day13/day13.h"
#include "../day14/day14.h"
#include "../day15/day15.h"
#include "../day16/day16.h"
#include "../day17/day17.h"
#include "../day18/day18.h"
#include "../day19/day19.h"
#include "../day20/day20.h"
#include "../day21/day21.h"
#include "../day22/day22.h"
#include "../day23/day23.h"
#include "../day24/day24.h"
#include "../day25/day25.h"
#include "../lib/aoc.h"
#include "../lib/puzzle.h"

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

void exec() {
    Puzzle<day01::ParsedInput> day01(aoc::Day01, day01::parse_input, day01::part1, day01::part2);
    day01.run();
    std::cout << std::endl;
}

TEST(perf, under_1_second) {
    auto t0 = std::chrono::high_resolution_clock::now();

    EXECUTE_DAY(01)
    EXECUTE_DAY(02)
    EXECUTE_DAY(03)
    EXECUTE_DAY(04)
    EXECUTE_DAY(05)
    EXECUTE_DAY(06)
    EXECUTE_DAY(07)
    EXECUTE_DAY(08)
    EXECUTE_DAY(09)
    EXECUTE_DAY(10)
    EXECUTE_DAY(11)
    EXECUTE_DAY(12)
    EXECUTE_DAY(13)
    EXECUTE_DAY(14)

    auto t_final = std::chrono::high_resolution_clock::now();

    std::cout << "Executed all days in "
              << std::chrono::duration_cast<std::chrono::microseconds>(t_final - t0) << std::endl;
}