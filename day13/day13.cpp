#include "day13.h"
#include "../lib/aoc.h"
#include "../lib/assert.h"
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <fstream>
#include <regex>

namespace day13 {

using namespace boost::numeric::ublas;

std::regex button_regex(R"(X\+(\d+), Y\+(\d+))");
std::regex prize_regex(R"(X=(\d+), Y=(\d+))");

aoc::Vector parse_button(const std::string &button_line) {
    auto button_begin = std::sregex_iterator(button_line.begin(),
                                             button_line.end(), button_regex);

    aoc_assert(button_begin != std::sregex_iterator(),
               "Button regex did not match");

    auto button_x = aoc::try_parse_int(button_begin->str(1));
    auto button_y = aoc::try_parse_int(button_begin->str(2));

    aoc_assert(button_x && button_y, "Button integer parse failure");

    return aoc::Vector{*button_x, *button_y};
}

LongPoint parse_prize(const std::string &prize_line) {
    auto prize_begin =
        std::sregex_iterator(prize_line.begin(), prize_line.end(), prize_regex);

    aoc_assert(prize_begin != std::sregex_iterator(),
               "Prize regex did not match");

    auto prize_x = aoc::try_parse_int(prize_begin->str(1));
    auto prize_y = aoc::try_parse_int(prize_begin->str(2));

    aoc_assert(prize_x && prize_y, "Prize integer parse failure");

    return LongPoint{*prize_x, *prize_y};
}

ParsedInput parse_input(std::ifstream &input_stream) {
    std::vector<ClawMachine> machines;

    while (!input_stream.eof()) {
        std::string button_a_line;
        std::string button_b_line;
        std::string prize_line;
        std::string empty_line;

        std::getline(input_stream, button_a_line);
        std::getline(input_stream, button_b_line);
        std::getline(input_stream, prize_line);
        std::getline(input_stream, empty_line);

        auto button_a = parse_button(button_a_line);
        auto button_b = parse_button(button_b_line);
        auto prize = parse_prize(prize_line);

        machines.emplace_back(button_a, button_b, prize);
    }

    return {machines};
}

matrix<double> invert_2x2(const matrix<double> &input) {
    double a = input(0, 0);
    double b = input(0, 1);
    double c = input(1, 0);
    double d = input(1, 1);

    double determinant = ((a * d) - (b * c));
    aoc_assert(determinant != 0, "Matrix cannot be inverted");

    matrix<double> result(2, 2);

    result(0, 0) = d;
    result(0, 1) = -b;
    result(1, 0) = -c;
    result(1, 1) = a;

    result /= determinant;

    return result;
}

bool is_integer(double value) {
    const auto epsilon = 1e-3;

    auto diff = value - std::round(value);
    return std::abs(diff) < epsilon;
}

long part1(const ParsedInput &input) {
    long min_cost = 0;

    for (const auto &machine : input.claw_machines) {
        /*
         * Let a_x, a_y = movement of button A
         *     b_x, b_y = movement of button B
         *     n_a, n_b = presses of button A and button B
         *     x,   y   = coordinates of the prize
         *
         * We can form a system of two simultaneous equations:
         *
         * n_a * a_x + n_b * b_x = x
         * n_a * a_y + n_b * b_y = y
         *
         * We need to check if these have a valid integer solution for n_a and
         * n_b.
         */

        // Matrix solution: Ax = B where x is the (n_a, n_b) vector
        // -> x = A^-1 * B;
        // This can have 0, 1, or an infinite number of solutions. It so happens
        // that all the cases in the puzzle input have 1 solution, _but_ this
        // may not be a valid solution due to requiring a non-integer number of
        // button presses.

        matrix<double> a(2, 2);
        matrix<double> b(2, 1);

        a(0, 0) = static_cast<double>(machine.a_button.dx);
        a(0, 1) = static_cast<double>(machine.b_button.dx);
        b(0, 0) = static_cast<double>(machine.prize_location.x);

        a(1, 0) = static_cast<double>(machine.a_button.dy);
        a(1, 1) = static_cast<double>(machine.b_button.dy);
        b(1, 0) = static_cast<double>(machine.prize_location.y);

        auto a_inverse = invert_2x2(a);
        auto solution = prod(a_inverse, b);

        double n_a = solution(0, 0);
        double n_b = solution(1, 0);

        if (is_integer(n_a) && is_integer(n_b)) {
            aoc_assert(n_a > 0 && n_b > 0,
                       "Negative button presses are not valid");

            min_cost += static_cast<long>(std::round(n_a) * 3);
            min_cost += static_cast<long>(std::round(n_b));
        }
    }

    return min_cost;
}

long part2(const ParsedInput &input) {
    std::vector<ClawMachine> new_machines;
    new_machines.reserve(input.claw_machines.size());

    for (const auto machine : input.claw_machines) {
        new_machines.emplace_back(
            machine.a_button, machine.b_button,
            LongPoint(machine.prize_location.x + 10000000000000,
                      machine.prize_location.y + 10000000000000));
    }

    return part1(ParsedInput(new_machines));
}

} // namespace day13
