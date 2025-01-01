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

TEST(perf, under_1_second) {
    using namespace aoc;

#ifndef NDEBUG
    std::cerr << "This test should be run in release mode" << std::endl;
    abort();
#endif

    // clang-format off
    Puzzle<day01::ParsedInput>         day01(Day01, day01::parse_input,         day01::part1,         day01::part2        );
    Puzzle<day02::ParsedInput>         day02(Day02, day02::parse_input,         day02::part1,         day02::part2        );
    Puzzle<day03::ParsedInput>         day03(Day03, day03::parse_input,         day03::part1,         day03::part2        );
    Puzzle<day04::ParsedInput>         day04(Day04, day04::parse_input,         day04::part1,         day04::part2        );
    Puzzle<day05::ParsedInput>         day05(Day05, day05::parse_input,         day05::part1,         day05::part2        );
    Puzzle<day06::ParsedInput>         day06(Day06, day06::parse_input,         day06::part1,         day06::faster::part2);
    Puzzle<day07::ParsedInput>         day07(Day07, day07::parse_input,         day07::faster::part1, day07::faster::part2);
    Puzzle<day08::ParsedInput>         day08(Day08, day08::parse_input,         day08::part1,         day08::part2        );
    Puzzle<day09::faster::ParsedInput> day09(Day09, day09::faster::parse_input, day09::faster::part1, day09::faster::part2);
    Puzzle<day10::ParsedInput>         day10(Day10, day10::parse_input,         day10::part1,         day10::part2        );
    Puzzle<day11::ParsedInput>         day11(Day11, day11::parse_input,         day11::part1,         day11::part2        );
    Puzzle<day12::ParsedInput>         day12(Day12, day12::parse_input,         day12::part1,         day12::part2        );
    Puzzle<day13::ParsedInput>         day13(Day13, day13::parse_input,         day13::part1,         day13::part2        );
    Puzzle<day14::ParsedInput>         day14(Day14, day14::parse_input,         day14::part1,         day14::part2        );
    Puzzle<day15::ParsedInput>         day15(Day15, day15::parse_input,         day15::part1,         day15::part2        );
    // clang-format on

    std::vector<PuzzleRunResult> results;

    auto t0 = std::chrono::high_resolution_clock::now();

    results.push_back(day01.run());
    results.push_back(day02.run());
    results.push_back(day03.run());
    results.push_back(day04.run());
    results.push_back(day05.run());
    results.push_back(day06.run());
    results.push_back(day07.run());
    results.push_back(day08.run());
    results.push_back(day09.run());
    results.push_back(day10.run());
    results.push_back(day11.run());
    results.push_back(day12.run());
    results.push_back(day13.run());
    results.push_back(day14.run()); // optimize this

    auto t_final = std::chrono::high_resolution_clock::now();

    for (const auto result : results) {
        auto day_fmt = std::format("{:02d}", static_cast<int>(result.day));

        std::cout << "Parsed day " << day_fmt << " input in " << std::setw(8) << result.parse_time
                  << std::endl;
        std::cout << "Ran day " << day_fmt << " part 1 in " << std::setw(10) << result.part_1_time
                  << std::endl;
        std::cout << "Ran day " << day_fmt << " part 2 in " << std::setw(10) << result.part_2_time
                  << std::endl;
        std::cout << std::endl;
    }

    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t_final - t0);
    std::cout << "Executed all days in " << total_duration << std::endl;

    ASSERT_LT(total_duration.count(), 1000);
}