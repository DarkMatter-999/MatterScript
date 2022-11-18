#include <stdio.h>
#include "compiler.h"

static void repl()
{
    char line[1024];
    while (1)
    {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin))
        {
            printf("\n");
            break;
        }
        compile(line);
    }
}

int main(int argc, const char *argv[])
{
    if (argc == 1)
    {
        repl();
    }
}