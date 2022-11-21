#if !defined(HASHTABLE_H)
#define HASHTABLE_H

#include "value.h"
#include <stdint.h>

typedef struct
{
    ObjString *key;
    Value value;
} Entry;

typedef struct
{
    int count;
    int capacity;
    Entry *entries;
} HashTable;

void initTable(HashTable *table);
void freeTable(HashTable *table);

bool tableSet(HashTable *table, ObjString *key, Value value);
bool tableDelete(HashTable *table, ObjString *key);
void tableAddAll(HashTable *from, HashTable *to);
ObjString *tableFindString(HashTable *table, const char *chars, int length, uint32_t hash);

#endif // HASHTABLE_H
