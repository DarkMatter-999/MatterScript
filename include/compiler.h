#if !defined(COMPILER_H)
#define COMPILER_H

#include <stdbool.h>
#include "bytecode.h"
#include "object.h"

ObjFunction *compile(const char *source);

#endif // COMPILER_H
