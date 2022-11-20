#include <memory.h>
#include <stdlib.h>

void *reallocate(void *pointer, size_t oldSize, size_t newSize)
{
    if (newSize == 0)
    {
        free(pointer);
        return NULL;
    }

    void *result = realloc(pointer, newSize);
    if (result == NULL)
        exit(1);
    return result;
}

int grow_capacity(int capacity)
{
    return ((capacity) < 8 ? 8 : (capacity)*2);
}

void *grow_array(int size, void *pointer, int oldCount, int newCount)
{
    return reallocate(pointer, size * (oldCount), size * (newCount));
}

void free_array(int size, void *pointer, int oldCount)
{
    reallocate(pointer, size * (oldCount), 0);
}