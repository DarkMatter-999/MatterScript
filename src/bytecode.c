#include <stdint.h>
#include "bytecode.h"
#include "memory.h"
#include "vm.h"
#include <stdint.h>

void initChunk(Chunk *chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line)
{
    if (chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = grow_capacity(oldCapacity);
        chunk->code = (uint8_t *)grow_array(sizeof(uint8_t), chunk->code,
                                            oldCapacity, chunk->capacity);
        chunk->lines = (int *)grow_array(sizeof(int), chunk->lines,
                                         oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

void freeChunk(Chunk *chunk)
{
    free_array(sizeof(uint8_t), chunk->code, chunk->capacity);
    free_array(sizeof(int), chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

int addConstant(Chunk *chunk, Value value)
{
    push(value);
    writeValueArray(&chunk->constants, value);
    pop();
    return chunk->constants.count - 1;
}
