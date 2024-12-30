//
// Created by jay on 30/12/24.
//

#ifndef PUZZLE_H
#define PUZZLE_H

#include <chrono>
#include <fstream>
#include <functional>

namespace aoc {

struct PuzzleRunResult {
    Day day;
    std::chrono::duration<long, std::ratio<1, 1000000>> parse_time;
    std::chrono::duration<long, std::ratio<1, 1000000>> part_1_time;
    std::chrono::duration<long, std::ratio<1, 1000000>> part_2_time;
};

template <typename Input> class Puzzle {
  public:
    Puzzle(Day day, std::function<Input(std::ifstream &)> parse_input,
           std::function<void(const Input &)> part1, std::function<void(const Input &)> part2)
        : day(day), parse_input(parse_input), part1(part1), part2(part2) {}

    [[nodiscard]] PuzzleRunResult run() const {
        using namespace std::chrono;

        std::string day_name = std::to_string(day);

        auto start = high_resolution_clock::now();

        auto input_stream = get_real_ifstream(day);
        Input input = this->parse_input(input_stream);

        auto parsed_input = high_resolution_clock::now();

        this->part1(input);
        auto part1_done = high_resolution_clock::now();

        this->part2(input);
        auto part2_done = high_resolution_clock::now();

        return {.day = this->day,
                .parse_time = duration_cast<microseconds>(parsed_input - start),
                .part_1_time = duration_cast<microseconds>(part1_done - parsed_input),
                .part_2_time = duration_cast<microseconds>(part2_done - part1_done)};
    }

  private:
    Day day;
    std::function<Input(std::ifstream &)> parse_input;
    std::function<void(const Input &)> part1;
    std::function<void(const Input &)> part2;
};
} // namespace aoc

#endif // PUZZLE_H
