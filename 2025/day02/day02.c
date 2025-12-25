#include "day02/day02.h"
#include "lib/string_split.h"

#include <stdio.h>

void day02_part1(FILE* /* file */) {
    const char* string = "Hello,world";

    struct StringSplitIterator* iter = string_split_create(string, ",");

    do {
        printf("segment: '%s'\n", string_split_current(iter));
    } while (string_split_move_next(iter));
}
