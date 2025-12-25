#ifndef AOC2025_LIB_STRING_H
#define AOC2025_LIB_STRING_H

struct String;

struct String* string_create(const char* value);

void string_append(struct String* string, const char* value);

char* string_data(struct String* string);

void string_trim_end(struct String* string, char target);

void string_free(struct String* string);

#endif // AOC2025_LIB_STRING_H

