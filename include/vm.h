#if !defined(VM_H)
#define VM_H

#include <stdint.h>
#include "bytecode.h"
#include "value.h"
#include "memory.h"

#define UINT8_COUNT (UINT8_MAX + 1)
#define FRAMES_MAX 64
#define STACK_MAX 256

// (FRAMES_MAX * UINT8_COUNT)

typedef struct
{
    uint8_t *ip;
    Chunk *chunk;
    Value stack[STACK_MAX];
    Value *stackTop;
    Obj *objects;
} VM;

typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();

InterpretResult interpret(const char *source);
void push(Value value);
Value pop();

static void resetStack();
static Value peek(int distance);
static void runtimeError(const char *format, ...);
static bool isFalsey(Value value);
static void concatenate();

#endif // VM_H
