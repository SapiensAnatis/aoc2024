//
// Created by jay on 03/12/24.
//

#include <vector>
#include <sstream>
#include <cassert>
#include "day2.h"

using namespace day2;

bool is_safe(const std::vector<int> &vec) {
    int first = vec[0];
    int second = vec[1];
    bool increasing = second > first;

    for (std::vector<int>::size_type i = 1; i < vec.size(); i++) {
        int current = vec[i];
        int previous = vec[i - 1];

        if (current > previous && !increasing) {
            return false;
        }

        if (current < previous && increasing) {
            return false;
        }

        int diff = std::abs(current - previous);

        if (diff < 1 || diff > 3) {
            return false;
        }
    }

    return true;
}

bool is_pair_safe(int current, int previous, bool increasing) {
    if (current > previous && !increasing) {
        return false;
    }

    if (current < previous && increasing) {
        return false;
    }

    int diff = std::abs(current - previous);

    if (diff < 1 || diff > 3) {
        return false;
    }

    return true;
}

bool is_safe_2(const std::vector<int> &vec) {
    int first = vec[0];
    int second = vec[1];
    bool increasing = second > first;
    bool problemDampenerTriggered = false;

    for (std::vector<int>::size_type i = 1; i < vec.size(); i++) {
        int current = vec[i];
        int previous = vec[i - 1];

        if (!is_pair_safe(current, previous, increasing)) {
            // Tolerance exceeded
            if (problemDampenerTriggered) {
                return false;
            }

            // Would removing the element at [i] fix it?
            // If we are at the last element, yes, otherwise yes if the next element and the previous are fine
            bool canRemoveCurrent = i == vec.size() - 1 || is_pair_safe(previous, vec[i + 1], increasing);
            if (canRemoveCurrent) {
                problemDampenerTriggered = true;
                if (i == 1) {
                    increasing = vec[2] > vec[0];
                }

                continue;
            }

            // Would removing the element at [i - 1] fix it?
            // If we are at the second element, yes, otherwise yes if the current element and the element before the previous element are fine
            bool canRemovePrevious = i == 1 || is_pair_safe(current, vec[i - 2], increasing);
            if (canRemovePrevious) {
                problemDampenerTriggered = true;
                if (i == 1) {
                    increasing = vec[2] > vec[1];
                }

                continue;
            }
        }
    }

    return true;
}


ParsedInput day2::parse_input(std::ifstream &input) {
    std::vector<std::vector<int>> reports;
    std::string line;

    while (std::getline(input, line)) {
        std::vector<int> levels;
        std::string levelStr;
        std::stringstream lineStream(line);

        while (std::getline(lineStream, levelStr, ' ')) {
            levels.push_back(std::stoi(levelStr));
        }

        reports.push_back(levels);
    }

    return ParsedInput{reports};
}

int day2::part1(const ParsedInput &input) {
    int safeReportCount = 0;

    for (const auto &report: input.reports) {
        if (is_safe(report)) {
            safeReportCount++;
        }
    }

    return safeReportCount;
}

int day2::part2(const ParsedInput &input) {
    int safeReportCount = 0;

    for (const auto &report: input.reports) {
        if (is_safe_2(report)) {
            safeReportCount++;
        }
    }

    return safeReportCount;
}
