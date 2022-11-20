#include <stdio.h>
#include "vm.h"
#include "bytecode.h"

static void repl()
{
    char line[1024];
    initVM();
    Chunk chunk;
    while (1)
    {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin))
        {
            printf("\n");
            break;
        }

        interpret(&chunk);
    }

    freeVM();
}

int main(int argc, const char *argv[])
{
    if (argc == 1)
    {
        repl();
    }
}