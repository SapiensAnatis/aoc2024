#ifndef AOC2024_DAY11_H
#define AOC2024_DAY11_H

#include <iostream>
#include <optional>
#include <vector>

namespace day11 {

struct StoneBlinkResult;

class Stone {
  public:
    explicit Stone(long number);

    [[nodiscard]] StoneBlinkResult blink() const;

    friend std::ostream &operator<<(std::ostream &stream, const Stone &stone);

    [[nodiscard]] long get_number() const;

  private:
    long number;
};

bool operator==(const Stone &a, const Stone &b);

struct StoneBlinkResult {
    StoneBlinkResult(Stone stone, std::optional<Stone> second_stone);

    Stone stone;
    std::optional<Stone> second_stone;
};

struct ParsedInput {
    std::vector<Stone> stones;
};

ParsedInput parse_input(std::ifstream &input_stream);

int part1(const ParsedInput &input, int num_blinks);

int part2(const ParsedInput &input, int num_blinks);

} // namespace day11

namespace std {
template <> struct hash<day11::Stone> {
    size_t operator()(const day11::Stone &stone) const;
};

} // namespace std

#endif // AOC2024_DAY11_H
