//
// Created by jay on 03/12/24.
//

#include "day2.h"
#include <sstream>
#include <vector>

namespace day2 {

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

bool is_safe(const std::vector<int> &report) {
    int first = report[0];
    int second = report[1];
    bool increasing = second > first;

    for (std::vector<int>::size_type i = 1; i < report.size(); i++) {
        int current = report[i];
        int previous = report[i - 1];

        if (!is_pair_safe(current, previous, increasing)) {
            return false;
        }
    }

    return true;
}

bool is_safe_2(const std::vector<int> &report) {
    int first = report[0];
    int second = report[1];
    bool increasing = second > first;

    for (std::vector<int>::size_type i = 1; i < report.size(); i++) {
        int current = report[i];
        int previous = report[i - 1];

        if (!is_pair_safe(current, previous, increasing)) {
            for (std::vector<int>::size_type j = 0; j < report.size(); j++) {
                std::vector<int> without_j(report.begin(), report.end());
                without_j.erase(
                    without_j.begin() +
                    static_cast<std::vector<int>::difference_type>(j));

                if (is_safe(without_j)) {
                    return true;
                }
            }

            return false;
        }
    }

    return true;
}

ParsedInput parse_input(std::ifstream &input) {
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

int part1(const ParsedInput &input) {
    int safeReportCount = 0;

    for (const auto &report : input.reports) {
        if (is_safe(report)) {
            safeReportCount++;
        }
    }

    return safeReportCount;
}

int part2(const ParsedInput &input) {
    int safeReportCount = 0;

    for (const auto &report : input.reports) {
        if (is_safe_2(report)) {
            safeReportCount++;
        }
    }

    return safeReportCount;
}
} // namespace day2