#include "day11.h"
#include "../lib/aoc.h"
#include <cassert>
#include <cmath>
#include <fstream>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>

namespace day11 {

Stone::Stone(long number) : number(number) {}

std::ostream &operator<<(std::ostream &stream, const Stone &stone) {
    return stream << stone.number;
}

StoneBlinkResult Stone::blink() const {
    if (this->number == 0) {
        return {Stone(1), std::nullopt};
    }

    std::string number_str = std::to_string(this->number);
    int digit_count = static_cast<int>(number_str.length());

    // std::cout << "digit_count(" << this->number << ") = " << digit_count
    //           << "\n";

    if (digit_count % 2 == 0) {
        std::string_view first_half_str(number_str.begin(),
                                        number_str.begin() + (digit_count / 2));
        std::string_view second_half_str(number_str.begin() + (digit_count / 2),
                                         number_str.end());

        auto first_half = aoc::stoi(first_half_str);
        auto second_half = aoc::stoi(second_half_str);

        assert(first_half && "blink: parse failure");
        assert(second_half && "blink: parse failure");

        return {Stone(*first_half), Stone(*second_half)};
    }

    return {Stone(this->number * 2024), std::nullopt};
}

StoneBlinkResult::StoneBlinkResult(Stone stone,
                                   std::optional<Stone> second_stone)
    : stone(stone), second_stone(second_stone) {}

ParsedInput parse_input(std::ifstream &input_stream) {
    std::string line;
    std::getline(input_stream, line);
    std::vector<Stone> stones;

    std::stringstream ss(line);
    long stone_num;
    while (ss >> stone_num) {
        stones.emplace_back(stone_num);
    }

    return {stones};
}

int part1(const ParsedInput &input) {
    int num_blinks = 6;
    std::vector<Stone> current_stone_array = input.stones;
    std::vector<Stone> next_stone_array;
    next_stone_array.reserve(current_stone_array.size());

    for (int i = 0; i < num_blinks; i++) {
        std::cout << "Blink: " << i << "\n";

        for (const auto &stone : current_stone_array) {
            std::cout << stone << " ";

            auto result = stone.blink();
            next_stone_array.push_back(result.stone);
            if (result.second_stone) {
                next_stone_array.push_back(*result.second_stone);
            }
        }

        std::cout << "\n";

        current_stone_array = next_stone_array;
    }

    return 0;
}

} // namespace day11
