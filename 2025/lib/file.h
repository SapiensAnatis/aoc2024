#ifndef AOC2025_LIB_FILE_H
#define AOC2025_LIB_FILE_H

#include <stdio.h>
#include <stdlib.h>

FILE* get_example_input(int day);

FILE* get_real_input(int day);

/**
 * Read a line from the given FILE* into the provided buffer.
 */
bool read_line(FILE* file, char* buffer, size_t buffer_size);

#endif // AOC2025_LIB_FILE_H
