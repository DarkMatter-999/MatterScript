#if !defined(DEBUG_H)
#define DEBUG_H

#include "value.h"
#include "bytecode.h"

#define DEBUG_SCANNER

#define DEBUG_PRINT_CODE

#define DEBUG_TRACE_EXECUTION

void disassembleChunk(Chunk *chunk, const char *name);
int disassembleInstruction(Chunk *chunk, int offset);

static int simpleInstruction(const char *name, int offset);
static int constantInstruction(const char *name, Chunk *chunk, int offset);
static int invokeInstruction(const char *name, Chunk *chunk, int offset);
static int byteInstruction(const char *name, Chunk *chunk, int offset);
static int jumpInstruction(const char *name, int sign, Chunk *chunk, int offset);

#endif // DEBUG_H
