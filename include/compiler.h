#if !defined(COMPILER_H)
#define COMPILER_H

#include <stdbool.h>
#include "bytecode.h"
#include "object.h"

bool compile(const char *source, Chunk *chunk);

#endif // COMPILER_H
