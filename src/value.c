#include "memory.h"
#include "value.h"
#include <stdlib.h>
#include <stdio.h>

void initValueArray(ValueArray *array)
{
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

void writeValueArray(ValueArray *array, Value value)
{
    if (array->capacity < array->count + 1)
    {
        int oldCapacity = array->capacity;
        array->capacity = grow_capacity(oldCapacity);
        array->values = grow_array(sizeof(Value), array->values,
                                   oldCapacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray *array)
{
    free_array(sizeof(Value), array->values, array->capacity);
    initValueArray(array);
}

void printValue(Value value)
{
    printf("%g", value);
}