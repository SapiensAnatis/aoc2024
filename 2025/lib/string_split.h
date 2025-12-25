#ifndef AOC2025_LIB_STRING_H
#define AOC2025_LIB_STRING_H

struct StringSplitIterator;

struct StringSplitIterator* string_split_create(const char* string, const char* separator);

bool string_split_move_next(struct StringSplitIterator* iter);

const char* string_split_current(const struct StringSplitIterator* iter);

void string_split_free(struct StringSplitIterator* iter);

#endif // AOC2025_LIB_STRING_H
