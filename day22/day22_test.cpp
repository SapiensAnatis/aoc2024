#include "../lib/aoc.h"
#include "../lib/assert.h"
#include "day22.h"

#include "gtest/gtest.h"

TEST(day22_part1, example) {
    std::array<day22::secret_number, 10> expected = {
        15887950, 16495136, 527345,   704524,  1553684,
        12683156, 11100544, 12249484, 7753432, 5908254};

    day22::secret_number result = 123;

    for (int i = 0; i < 10; i++) {
        result = day22::advance_number_once(result);
        std::cout << result << std::endl;
        EXPECT_EQ(result, expected[i]) << "Wrong secret number evolution";
    }
}

TEST(day22_part1, example2) {
    auto input_stream = aoc::get_example_ifstream();
    auto input = day22::parse_input(input_stream);

    auto result = day22::part1(input);

    std::cout << result << std::endl;

    EXPECT_EQ(result, 37327623) << "Does not match example";
}

TEST(day22_part1, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day22::parse_input(input_stream);

    auto result = day22::part1(input);

    std::cout << result << std::endl;
}

TEST(day22_part2, example) {
    auto result = day22::advance_number_and_track_changes(123, 10);

    day22::ChangeSequence should_win_6(-1, -1, 0, 2);

    EXPECT_EQ(result.at(should_win_6), 6) << "Did not win 6 bananas";
}

TEST(day22_part2, example2) {
    auto input_stream = aoc::get_example_ifstream(2);
    auto input = day22::parse_input(input_stream);

    auto result = day22::part2(input);

    std::cout << result << std::endl;

    EXPECT_EQ(result, 23) << "Does not match example";
}

TEST(day22_part2, real) {
    auto input_stream = aoc::get_real_ifstream();
    auto input = day22::parse_input(input_stream);

    auto result = day22::part2(input);

    std::cout << result << std::endl;
}
