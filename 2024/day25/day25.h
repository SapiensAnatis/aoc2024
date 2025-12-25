#ifndef AOC2024_DAY25_H
#define AOC2024_DAY25_H
#include <fstream>
#include <vector>

namespace day25 {

struct Lock {
    // Height from top
    int pin1, pin2, pin3, pin4, pin5;

    Lock(int pin1, int pin2, int pin3, int pin4, int pin5)
        : pin1(pin1), pin2(pin2), pin3(pin3), pin4(pin4), pin5(pin5) {}
};

struct Key {
    // Height from bottom
    int pin1, pin2, pin3, pin4, pin5;

    Key(int pin1, int pin2, int pin3, int pin4, int pin5)
        : pin1(pin1), pin2(pin2), pin3(pin3), pin4(pin4), pin5(pin5) {}
};

struct ParsedInput {
    std::vector<Lock> locks;
    std::vector<Key> keys;
};

ParsedInput parse_input(std::ifstream &input);

int part1(const ParsedInput &input);

} // namespace day25

#endif // AOC2024_DAY25_H
