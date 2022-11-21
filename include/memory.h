#if !defined(MEM_H)
#define MEM_H

#include <stdint.h>
#include <stddef.h>
#include "object.h"

void *reallocate(void *pointer, size_t oldSize, size_t newSize);

int grow_capacity(int capacity);

void *grow_array(int size, void *pointer, int oldCount, int newCount);

void free_array(int size, void *pointer, int oldCount);

void *allocate(int size, int count);

void free_(int size, void *pointer);

void freeObjects();

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity)*2)

#define GROW_ARRAY(type, pointer, oldCount, newCount)      \
    (type *)reallocate(pointer, sizeof(type) * (oldCount), \
                       sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

#define ALLOCATE(type, count) \
    (type *)reallocate(NULL, 0, sizeof(type) * (count))

#define FREE(type, pointer) reallocate(pointer, sizeof(type), 0)

#endif // MEM_H
