#if !defined(VM_H)
#define VM_H

#include <stdint.h>
#include "bytecode.h"
#include "value.h"
#include "memory.h"
#include "object.h"
#include "hashtable.h"

#define UINT8_COUNT (UINT8_MAX + 1)
#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct
{
    ObjClosure *closure;
    uint8_t *ip;
    Value *slots;
} CallFrame;

typedef struct
{
    CallFrame frames[FRAMES_MAX];
    int frameCount;

    Value stack[STACK_MAX];
    Value *stackTop;
    Obj *objects;
    HashTable strings;
    ObjUpvalue *openUpvalues;
    HashTable globals;
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

static bool call(ObjClosure *closure, int argCount);
static bool callValue(Value callee, int argCount);
static void defineNative(const char *name, NativeFn function);

static ObjUpvalue *captureUpvalue(Value *local);
static void closeUpvalues(Value *last);

#endif // VM_H
