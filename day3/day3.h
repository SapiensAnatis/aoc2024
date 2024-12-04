#ifndef AOC2024_DAY1_H
#define AOC2024_DAY1_H

#include <vector>

namespace day3 {
    struct ParsedInput {
        std::vector<MultiplyInstruction> instructions;
    };

    struct MultiplyInstruction {
        int multiplier;
        int multiplicand;
    };
}

#endif // AOC2024_DAY1_H