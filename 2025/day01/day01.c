#include "day01/day01.h"
#include "lib/vector.h"

#include <stdint.h>
#include <stdio.h>

enum DialDirection { LEFT, RIGHT };

struct DialRotation {
    enum DialDirection direction;
    int32_t rotations;
};

int main() {
    struct Vector* my_vector = vector_create(sizeof(int));

    for (int i = 0; i < 10; i++) {
        vector_append(my_vector, &i);
    }

    for (size_t i = 0; i < vector_size(my_vector); i++) {
        printf("Vector element: %d\n", *(int*)vector_at(my_vector, i));
    }

    vector_free(my_vector);
}
