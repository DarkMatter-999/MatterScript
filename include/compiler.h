#if !defined(COMPILER_H)
#define COMPILER_H

#include <stdbool.h>
#include "bytecode.h"
#include "object.h"

ObjFunction *compile(const char *source);

void markCompilerRoots();

#endif // COMPILER_H
