#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include "day1.h"

ParsedInput parse_input(const std::string &path) {
    std::ifstream inputStream(path);
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

    return ParsedInput { .left =  left, .right =  right };
}

int part1(ParsedInput &input) {
    std::sort(input.left.begin(), input.left.end());
    std::sort(input.right.begin(), input.right.end());

    int totalDistance = 0;

    for (int i = 0; i < input.left.size(); i++) {
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
        auto [iter, inserted] = numberOccurrenceCounts.insert(std::map<int, int>::value_type(num, 0));
        iter->second += 1;
    }

    int similarityScore = 0;

    for (auto num : input.left) {
        auto occurrenceCountIter = numberOccurrenceCounts.find(num);
        auto occurrenceCount = (occurrenceCountIter != numberOccurrenceCounts.end())
                ? occurrenceCountIter->second
                : 0;
        similarityScore += num * occurrenceCount;
    }

    return similarityScore;
}