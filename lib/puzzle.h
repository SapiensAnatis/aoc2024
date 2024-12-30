//
// Created by jay on 30/12/24.
//

#ifndef PUZZLE_H
#define PUZZLE_H

#include <chrono>
#include <fstream>
#include <functional>

template <typename Input> class Puzzle {
  public:
    Puzzle(aoc::Day day, std::function<Input(std::ifstream &)> parse_input,
           std::function<void(const Input &)> part1, std::function<void(const Input &)> part2)
        : day(day), parse_input(parse_input), part1(part1), part2(part2) {}

    void run() const {
        std::string day_name = std::to_string(day);

        auto t1 = std::chrono::high_resolution_clock::now();

        auto input_stream = get_real_ifstream(day);
        Input input = this->parse_input(input_stream);

        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "Parsed day " << day_name << " input in "
                  << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1) << std::endl;

        this->part1(input);
        auto t3 = std::chrono::high_resolution_clock::now();

        std::cout << "Ran day " << day_name << " part 1 in "
                  << std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2) << std::endl;

        this->part2(input);
        auto t4 = std::chrono::high_resolution_clock::now();

        std::cout << "Ran day " << day_name << " part 2 in "
                  << std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3) << std::endl << std::endl;
    }

  private:
    aoc::Day day;
    std::function<Input(std::ifstream &)> parse_input;
    std::function<void(const Input &)> part1;
    std::function<void(const Input &)> part2;
};

#endif // PUZZLE_H
