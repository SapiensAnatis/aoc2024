#include "lib/debug.h"
#include "lib/vector.h"

#include <assert.h>
#include <malloc.h>
#include <string.h>

struct Vector {
    void *data;
    size_t size;
    size_t capacity;
    size_t elementSize;
};

constexpr size_t VectorInitialCapacity = 4;

struct Vector *vector_create(size_t elementSize) {
    DEBUG_PRINT("Creating new vector with elementSize %d", elementSize);

    struct Vector *result = malloc(sizeof(struct Vector));
    assert(result != nullptr && "failed to allocate vector");

    void *data = malloc(elementSize * VectorInitialCapacity);
    assert(data != nullptr && "failed to allocate vector data");

    result->data = data;
    result->size = 0;
    result->capacity = VectorInitialCapacity;
    result->elementSize = elementSize;

    return result;
}

void *vector_at(const struct Vector *vector, size_t index) {
    assert(index < vector->size && "out of bounds accesss to vector");

    void *elementPtr = ((char *)vector->data) + (index * vector->elementSize);

    return elementPtr;
}

void vector_append(struct Vector *vector, const void *element) {
    DEBUG_PRINT("Appending element to vector at %p: %p", vector, element);

    if (vector->size == vector->capacity) {
        size_t newCapacity = vector->capacity * 2;

        DEBUG_PRINT("Expanding vector at %p: from %zu to %zu", vector, vector->capacity,
                    newCapacity);

        void *newData = realloc(vector->data, newCapacity * vector->elementSize);
        assert(newData != nullptr && "failed to allocate expanded vector data");

        vector->capacity = newCapacity;
        vector->data = newData;
    }

    void *dest = ((char *)vector->data) + (vector->size * vector->elementSize);

    memcpy(dest, element, vector->elementSize);
    vector->size += 1;
}

size_t vector_size(const struct Vector *vector) { return vector->size; }

void vector_free(struct Vector *vector) {
    DEBUG_PRINT("Destroying vector at %p", vector);

    free(vector->data);
    free(vector);
}
