#include "day03/day03.h"
#include "lib/debug.h"
#include "lib/file.h"
#include "lib/string.h"
#include "lib/string_split.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int find_max_jolts(const char* line) {
    DEBUG_PRINT("Analysing line: '%s'", line);

    int max_digit = 0;
    size_t max_digit_position = 0;
    size_t line_length = strlen(line);

    for (size_t i = 0; i < line_length; i++) {
        char ch = line[i];
        int digit = ch - '0';
        if (digit > max_digit) {
            max_digit = digit;
            max_digit_position = i;
        }
    }

    int second_max_digit = 0;
    size_t start_search_pos = (max_digit_position + 1) % line_length;
    size_t second_max_digit_position = 0;

    for (size_t i = start_search_pos; i < line_length && i != max_digit_position; i++) {
        char ch = line[i];
        int digit = ch - '0';
        if (digit > second_max_digit) {
            second_max_digit = digit;
            second_max_digit_position = i;
        }
    }

    assert(second_max_digit_position != max_digit_position);

    int answer = max_digit_position < second_max_digit_position
                     ? (max_digit * 10) + second_max_digit
                     : (second_max_digit * 10) + max_digit;

    DEBUG_PRINT("Max jolts: %d", answer);

    return answer;
}

void day03_part1(FILE* file) {
    struct String* string = read_all_text(file);
    string_trim_end(string, '\n');

    const char* string_buffer = string_data(string);

    int answer = 0;

    struct StringSplitIterator* iter = string_split_create(string_buffer, "\n");
    do {
        const char* line = string_split_current(iter);
        answer += find_max_jolts(line);
    } while (string_split_move_next(iter));

    printf("Answer: %d\n", answer);
}
