#include "day11.h"
#include "../lib/aoc.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <numeric>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace day11 {

Stone::Stone(long number) : number(number) {}

std::ostream &operator<<(std::ostream &stream, const Stone &stone) {
    return stream << stone.number;
}

StoneBlinkResult Stone::blink() const {
    assert(this->number >= 0 && "Negative stone number!");

    if (this->number == 0) {
        return {Stone(1), std::nullopt};
    }

    std::string number_str = std::to_string(this->number);
    int digit_count = static_cast<int>(number_str.length());

    // std::cout << "digit_count(" << this->number << ") = " << digit_count
    //           << std::endl;

    if (digit_count % 2 == 0) {
        std::string_view first_half_str(number_str.begin(), number_str.begin() + (digit_count / 2));
        std::string_view second_half_str(number_str.begin() + (digit_count / 2), number_str.end());

        auto first_half = aoc::try_parse_int(first_half_str);
        auto second_half = aoc::try_parse_int(second_half_str);

        assert(first_half && "blink: parse failure");
        assert(second_half && "blink: parse failure");

        return {Stone(*first_half), Stone(*second_half)};
    }

    return {Stone(this->number * 2024), std::nullopt};
}

long Stone::get_number() const { return this->number; }

bool operator==(const Stone &a, const Stone &b) { return a.get_number() == b.get_number(); }

StoneBlinkResult::StoneBlinkResult(Stone stone, std::optional<Stone> second_stone)
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

long puzzle(const ParsedInput &input, int num_blinks) {
    std::unordered_map<Stone, long> stone_occurrence_counts;

    for (const auto &stone : input.stones) {
        auto [it, inserted] = stone_occurrence_counts.emplace(stone, 0);
        it->second++;
    }

    for (int blink = 0; blink < num_blinks; blink++) {
        std::unordered_map<Stone, long> new_stone_occurrence_counts;
        new_stone_occurrence_counts.reserve(stone_occurrence_counts.size());

        for (const auto &[stone, count] : stone_occurrence_counts) {
            auto result = stone.blink();

            auto [it, _] = new_stone_occurrence_counts.emplace(result.stone, 0);
            it->second += count;

            if (result.second_stone) {
                auto [it_2, _] = new_stone_occurrence_counts.emplace(*result.second_stone, 0);
                it_2->second += count;
            }
        }

        stone_occurrence_counts = new_stone_occurrence_counts;
    }

    return std::accumulate(
        stone_occurrence_counts.begin(), stone_occurrence_counts.end(), 0L,
        [](const long acc, const std::pair<Stone, long> &pair) { return acc + pair.second; });
}

int part1(const ParsedInput &input) { return static_cast<int>(puzzle(input, 25)); }

long part2(const ParsedInput &input) { return puzzle(input, 75); }

} // namespace day11

namespace std {
size_t hash<day11::Stone>::operator()(const day11::Stone &stone) const noexcept {
    return hash<long>()(stone.get_number());
}
} // namespace std