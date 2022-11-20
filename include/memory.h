#if !defined(MEM_H)
#define MEM_H

#include <stdint.h>
#include <stddef.h>

void *reallocate(void *pointer, size_t oldSize, size_t newSize);

int grow_capacity(int capacity);

void *grow_array(int size, void *pointer, int oldCount, int newCount);

void free_array(int size, void *pointer, int oldCount);

#endif // MEM_H
