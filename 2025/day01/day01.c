#include "day01/day01.h"
#include "lib/file.h"

#include <stdint.h>
#include <stdio.h>

enum DialDirection { LEFT, RIGHT };

struct DialRotation {
    enum DialDirection direction;
    int32_t rotations;
};

int main() {
    FILE* example = get_example(1);

    char line_buffer[1024];
    while (read_line(example, line_buffer, sizeof(line_buffer))) {
        printf("Line: '%s'\n", line_buffer);
    }
}
