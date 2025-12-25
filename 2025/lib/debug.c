#include "lib/debug.h"

#include <stdarg.h>
#include <stdio.h>

void debug_print(const char *file, int line, const char *fmt, ...) {
    fprintf(stderr, "[%s:%d] ", file, line);

    va_list ptr;
    va_start(ptr, fmt);
    vfprintf(stderr, fmt, ptr);
    va_end(ptr);

    fprintf(stderr, "\n");
}
