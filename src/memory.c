#include "memory.h"
#include <stdlib.h>
#include "vm.h"

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

static void freeObject(Obj *object)
{
    switch (object->type)
    {
    case OBJ_FUNCTION:
    {
        ObjFunction *function = (ObjFunction *)object;
        freeChunk(&function->chunk);
        FREE(ObjFunction, object);
        break;
    }
    case OBJ_STRING:
    {
        ObjString *string = (ObjString *)object;
        free_array(sizeof(char), string->chars, string->length + 1);
        free_(sizeof(ObjString), object);
        break;
    }
    }
}

void freeObjects()
{
    Obj *object = vm.objects;
    while (object != NULL)
    {
        Obj *next = object->next;
        freeObject(object);
        object = next;
    }
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

void *allocate(int size, int count)
{
    return reallocate(NULL, 0, size * (count));
}

void free_(int size, void *pointer)
{
    reallocate(pointer, size, 0);
}