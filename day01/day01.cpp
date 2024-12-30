#include "day01.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace day01 {
ParsedInput parse_input(std::ifstream &inputStream) {
    std::string line;
    std::string delimiter = "   ";

    std::vector<int> left;
    std::vector<int> right;

    while (std::getline(inputStream, line)) {
        auto delimiterIndex = line.find(delimiter);
        std::string leftToken = line.substr(0, delimiterIndex);
        left.push_back(std::stoi(leftToken));

        line.erase(0, delimiterIndex + delimiter.length());

        delimiterIndex = line.find(delimiter);
        std::string rightToken = line.substr(0, delimiterIndex);
        right.push_back(std::stoi(rightToken));
    }

    return ParsedInput{.left = left, .right = right};
}

int part1(const ParsedInput &input) {
    auto left_copy = input.left;
    auto right_copy = input.right;

    std::ranges::sort(left_copy);
    std::ranges::sort(right_copy);

    int totalDistance = 0;

    for (std::vector<int>::size_type i = 0; i < input.left.size(); i++) {
        int leftNum = input.left[i];
        int rightNum = input.right[i];

        int distance = std::abs(leftNum - rightNum);
        totalDistance += distance;
    }

    return totalDistance;
}

int part2(const ParsedInput &input) {
    std::map<int, int> numberOccurrenceCounts;

    for (auto num : input.right) {
        auto [iter, inserted] =
            numberOccurrenceCounts.insert(std::map<int, int>::value_type(num, 0));
        iter->second += 1;
    }

    int similarityScore = 0;

    for (auto num : input.left) {
        auto occurrenceCountIter = numberOccurrenceCounts.find(num);
        auto occurrenceCount =
            (occurrenceCountIter != numberOccurrenceCounts.end()) ? occurrenceCountIter->second : 0;
        similarityScore += num * occurrenceCount;
    }

    return similarityScore;
}
} // namespace day01