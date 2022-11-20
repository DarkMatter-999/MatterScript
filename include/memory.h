#if !defined(MEM_H)
#define MEM_H

#include <stdint.h>
#include <stddef.h>

void *reallocate(void *pointer, size_t oldSize, size_t newSize);

int grow_capacity(int capacity);

void *grow_array(int size, void *pointer, int oldCount, int newCount);

void free_array(int size, void *pointer, int oldCount);

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity)*2)

#define GROW_ARRAY(type, pointer, oldCount, newCount)      \
    (type *)reallocate(pointer, sizeof(type) * (oldCount), \
                       sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

#endif // MEM_H
