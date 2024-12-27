#include "day22.h"

#include "../lib/aoc.h"
#include "../lib/assert.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>

namespace day22 {

ParsedInput parse_input(std::ifstream &input) {
    std::string line;
    std::vector<secret_number> numbers{};

    while (std::getline(input, line)) {
        numbers.push_back(aoc::parse_int(line));
    }

    return {.initial_numbers = numbers};
}

secret_number mix_number(secret_number a, secret_number b) { return a ^ b; }

secret_number prune_number(secret_number a) { return a % 16777216; }

secret_number advance_number_once(secret_number number) {
    secret_number result = mix_number(number, number * 64);
    result = prune_number(result);
    result = mix_number(result, result / 32);
    result = prune_number(result);
    result = mix_number(result, result * 2048);
    result = prune_number(result);
    return result;
}

secret_number advance_number(secret_number number, int iterations) {
    secret_number result = number;

    for (int i = 0; i < iterations; i++) {
        result = advance_number_once(result);
    }

    return result;
}

secret_number part1(const ParsedInput &input) {
    secret_number result = 0;

    for (auto number : input.initial_numbers) {
        auto advanced = advance_number(number, 2000);
        std::cout << number << ": " << advanced << std::endl;
        result += advanced;
    }

    return result;
}

std::unordered_map<ChangeSequence, secret_number>
advance_number_and_track_changes(secret_number init_number, int iterations) {
    secret_number previous_number = init_number;
    std::deque<int> changes_deque;

    std::unordered_map<ChangeSequence, secret_number> change_sequence_values;
    change_sequence_values.reserve(iterations);

    for (int i = 0; i < iterations; i++) {

        auto number = advance_number_once(previous_number);
        int price = static_cast<int>(number % 10);
        int previous_price = static_cast<int>(previous_number % 10);

        int change = price - previous_price;

        changes_deque.push_back(change);

        if (changes_deque.size() >= 4) {
            if (changes_deque.size() >= 5) {
                changes_deque.pop_front();
            }

            ChangeSequence change_sequence =
                ChangeSequence::create(changes_deque);

            // It doesn't matter if the insert fails - if we've seen this change
            // before, then we don't care about recording further results for
            // it.
            change_sequence_values.emplace(change_sequence, price);
        }

        previous_number = number;
    }

    return change_sequence_values;
}

secret_number part2(const ParsedInput &input) {
    std::unordered_map<ChangeSequence, secret_number> all_change_values;

    for (auto number : input.initial_numbers) {
        auto change_values = advance_number_and_track_changes(number, 2000);

        for (const auto &pair : change_values) {
            all_change_values.emplace(pair.first, 0);
            all_change_values[pair.first] += pair.second;
        }
    }

    // find best key in all_change_values
    auto best_change_it =
        std::max_element(all_change_values.begin(), all_change_values.end(),
                         [](auto a, auto b) { return a.second < b.second; });

    aoc_assert(best_change_it != all_change_values.end(),
               "failed to find max element");

    return best_change_it->second;
}

} // namespace day22
