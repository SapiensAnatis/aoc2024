#include "lib/debug.h"
#include "lib/string_split.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct StringSplitIterator {
    const char* string;
    size_t string_length;
    const char* separator;
    size_t current_position;
    char* current_segment;
    size_t current_segment_length;
};

struct StringSplitIterator* string_split_create(const char* string, const char* separator) {
    struct StringSplitIterator* iter = malloc(sizeof(struct StringSplitIterator));
    assert(iter != nullptr && "struct allocation failed");

    iter->string = string;
    iter->string_length = strlen(iter->string);
    iter->separator = separator;
    iter->current_position = 0;

    const char* next_ptr = strstr(iter->string, iter->separator);
    if (next_ptr == nullptr) {
        // String does not contain separator. Yield a single segment which is just the entire
        // string.
        iter->current_segment = strdup(iter->string);
        iter->current_segment_length = strlen(iter->current_segment);

        DEBUG_PRINT("Created single-segment StringSplitIterator: '%s'", iter->current_segment);
    } else {
        iter->current_segment = malloc(strlen(iter->string) + 1);
        assert(iter->current_segment != nullptr && "struct->current_segment allocation failed");

        size_t segment_length = next_ptr - iter->string;
        memcpy(iter->current_segment, iter->string, segment_length);
        iter->current_segment[segment_length] = '\0';
        iter->current_segment_length = segment_length;

        DEBUG_PRINT("Created StringSplitIterator with initial segment: '%s'",
                    iter->current_segment);
    }

    return iter;
}

bool string_split_move_next(struct StringSplitIterator* iter) {
    size_t search_start_position =
        iter->current_position + iter->current_segment_length + strlen(iter->separator);

    if (search_start_position > iter->string_length) {
        DEBUG_PRINT("No further segments in StringSplitIterator");
        return false;
    }

    const char* search_start = iter->string + search_start_position;
    const char* next_ptr = strstr(search_start, iter->separator);

    if (next_ptr == nullptr) {
        // No further segment. Return the remainder of the string.
        size_t bytes_left = iter->string_length - search_start_position;
        memcpy(iter->current_segment, search_start, bytes_left);
        iter->current_segment[bytes_left] = '\0';
        iter->current_position = search_start_position;
        iter->current_segment_length = bytes_left;

        DEBUG_PRINT("Reached last split segment in string: '%s'", iter->current_segment);
    } else {
        size_t segment_size = next_ptr - search_start;
        memcpy(iter->current_segment, search_start, segment_size);
        iter->current_segment[segment_size] = '\0';
        iter->current_position = search_start_position;
        iter->current_segment_length = segment_size;

        DEBUG_PRINT("Reached next split segment in string: '%s'", iter->current_segment);
    }

    return true;
}

const char* string_split_current(const struct StringSplitIterator* iter) {
    return iter->current_segment;
}

void string_split_free(struct StringSplitIterator* iter) {
    free(iter->current_segment);
    free(iter);
}
