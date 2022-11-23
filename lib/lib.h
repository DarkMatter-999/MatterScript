#if !defined(LIB_H)
#define LIB_H

#include <time.h>
#include <stdlib.h>
#include "value.h"

static Value clockNative(int argCount, Value *args)
{
    return NUMBER_VAL((double)clock() / CLOCKS_PER_SEC);
}

static Value exit_(int argCount, Value *args)
{
    exit(0);
}

#endif // LIB_H
