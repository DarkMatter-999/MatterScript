#if !defined(VM_H)
#define VM_H

#include <stdint.h>
#include "bytecode.h"
#include "value.h"

#define UINT8_COUNT (UINT8_MAX + 1)
#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct
{
    uint8_t *ip;
    Chunk *chunk;
    Value stack[STACK_MAX];
    Value *stackTop;
} VM;

typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();

InterpretResult interpret(Chunk *chunk);

#endif // VM_H
