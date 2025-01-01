//
// Created by jay on 01/01/25.
//

#include "../lib/assert.h"
#include "day07.h"

#include <cmath>
#include <iostream>
#include <ranges>

namespace day07::faster {

constexpr long pow(int x, int y) {
    long i = 1;
    for (int j = 0; j < y; j++) {
        i *= x;
    }
    return i;
}

constexpr std::array powers_of_ten = {
    pow(10, 0), pow(10, 1), pow(10, 2), pow(10, 3), pow(10, 4),  pow(10, 5),
    pow(10, 6), pow(10, 7), pow(10, 8), pow(10, 9), pow(10, 10),
};

int get_digit_count(long a) {
    for (std::array<int, 10>::size_type i = 1; i < powers_of_ten.size(); i++) {
        if (powers_of_ten[i] == a) {
            return static_cast<int>(i + 1);
        }
        if (powers_of_ten[i] > a) {
            return static_cast<int>(i);
        }
    }

    aoc_assert(false, "failed to get digit count");
    return -1;
}

long inverse_concat(long a, long b) {
    auto digit_count = get_digit_count(b);
    // Subtract b from a and shift to the right
    return (a - b) / powers_of_ten[digit_count];
}

bool ends_with(long a, long ends_width) {
    auto digit_count = get_digit_count(ends_width);
    auto ten_exp = powers_of_ten[digit_count];

    return (a % ten_exp) == ends_width;
}

// NOLINTNEXTLINE(misc-no-recursion)
bool check_operands_can_make(const std::vector<int> &operands, bool enable_concat,
                             std::vector<int>::size_type index, long test_value) {
    auto operand = operands[index];

    if (index == 0) {
        // If the operation was possible, then all of our inputs until now will have reversed
        // the test value to retrieve the first operand
        return operand == test_value;
    }

    // Was the operation multiplication?
    if (test_value % operand == 0) {
        auto new_test_value = test_value / operand;
        if (check_operands_can_make(operands, enable_concat, index - 1, new_test_value)) {
            return true;
        }
    }

    // Was the operation concatenation?
    if (enable_concat && ends_with(test_value, operand)) {
        auto new_test_value = inverse_concat(test_value, operand);
        if (check_operands_can_make(operands, enable_concat, index - 1, new_test_value)) {
            return true;
        }
    }

    // We can't rule out the operation being addition. We'll have to disprove this by reaching
    // the base case with a non-matching value
    auto new_test_value = test_value - operand;
    return check_operands_can_make(operands, enable_concat, index - 1, new_test_value);
}

bool check_operation_possible(const Operation &operation, bool enable_concat) {
    return check_operands_can_make(operation.operands, enable_concat, operation.operands.size() - 1,
                                   operation.result);
}

long part1(const ParsedInput &input) {
    long result = 0;

    for (const auto &operation : input.operations) {
        if (check_operation_possible(operation, false)) {
            result += operation.result;
        }
    }

    return result;
}

long part2(const ParsedInput &input) {
    long result = 0;

    for (const auto &operation : input.operations) {
        if (check_operation_possible(operation, true)) {
            result += operation.result;
        }
    }

    return result;
}

} // namespace day07::faster