#include "compiler.h"
#include "scanner.h"

void compile(const char *source)
{
    // printf("%s", source);
    initScanner(source);

    Token t = scanToken();
    while (t.type != TOKEN_EOF)
    {
        t = scanToken();
    }
}