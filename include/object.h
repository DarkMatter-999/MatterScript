#if !defined(OBJECT_H)
#define OBJECT_H

#include "value.h"
#include "hashtable.h"
#include "bytecode.h"
#include <stdint.h>

#define OBJ_TYPE(value) (AS_OBJ(value)->type)
#define IS_BOUND_METHOD(value) isObjType(value, OBJ_BOUND_METHOD)
#define IS_LIST(value) isObjType(value, OBJ_LIST)
#define IS_CLASS(value) isObjType(value, OBJ_CLASS)
#define IS_CLOSURE(value) isObjType(value, OBJ_CLOSURE)
#define IS_FUNCTION(value) isObjType(value, OBJ_FUNCTION)
#define IS_INSTANCE(value) isObjType(value, OBJ_INSTANCE)
#define IS_NATIVE(value) isObjType(value, OBJ_NATIVE)
#define IS_STRING(value) isObjType(value, OBJ_STRING)

#define AS_BOUND_METHOD(value) ((ObjBoundMethod *)AS_OBJ(value))
#define AS_LIST(value) ((ObjList *)AS_OBJ(value))
#define AS_CLASS(value) ((ObjClass *)AS_OBJ(value))
#define AS_CLOSURE(value) ((ObjClosure *)AS_OBJ(value))
#define AS_FUNCTION(value) ((ObjFunction *)AS_OBJ(value))
#define AS_INSTANCE(value) ((ObjInstance *)AS_OBJ(value))
#define AS_NATIVE(value) \
    (((ObjNative *)AS_OBJ(value))->function)
#define AS_STRING(value) ((ObjString *)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString *)AS_OBJ(value))->chars)

typedef enum
{
    OBJ_BOUND_METHOD,
    OBJ_CLASS,
    OBJ_CLOSURE,
    OBJ_FUNCTION,
    OBJ_INSTANCE,
    OBJ_LIST,
    OBJ_NATIVE,
    OBJ_STRING,
    OBJ_UPVALUE
} ObjType;

struct Obj
{
    ObjType type;
    bool isMarked;
    struct Obj *next;
};

typedef struct
{
    Obj obj;
    int arity;
    int upvalueCount;
    Chunk chunk;
    ObjString *name;
} ObjFunction;

typedef Value (*NativeFn)(int argCount, Value *args);

typedef struct
{
    Obj obj;
    NativeFn function;
} ObjNative;

struct ObjString
{
    Obj obj;
    int length;
    char *chars;
    uint32_t hash;
};

typedef struct ObjUpvalue
{
    Obj obj;
    Value *location;
    Value closed;
    struct ObjUpvalue *next;
} ObjUpvalue;

typedef struct
{
    Obj obj;
    ObjFunction *function;
    ObjUpvalue **upvalues;
    int upvalueCount;
} ObjClosure;

typedef struct
{
    Obj obj;
    ObjString *name;
    HashTable methods;
} ObjClass;

typedef struct
{
    Obj obj;
    ObjClass *klass;
    HashTable fields;
} ObjInstance;

typedef struct
{
    Obj obj;
    Value receiver;
    ObjClosure *method;
} ObjBoundMethod;

typedef struct
{
    Obj obj;
    int count;
    int capacity;
    Value *items;
} ObjList;

ObjBoundMethod *newBoundMethod(Value receiver, ObjClosure *method);

ObjClass *newClass(ObjString *name);

ObjClosure *newClosure(ObjFunction *function);

ObjFunction *newFunction();

ObjInstance *newInstance(ObjClass *klass);

ObjNative *newNative(NativeFn function);

ObjString *copyString(const char *chars, int length);

ObjUpvalue *newUpvalue(Value *slot);

void printObject(Value value);
ObjString *takeString(char *chars, int length);
static ObjString *allocateString(char *chars, int length, uint32_t hash);

ObjList *newList();
void appendToList(ObjList *list, Value value);
void storeToList(ObjList *list, int index, Value value);
Value indexFromList(ObjList *list, int index);
Value indexFromString(ObjString *string, int index);
void deleteFromList(ObjList *list, int index);
bool isValidListIndex(ObjList *list, int index);
bool isValidStringIndex(ObjString *string, int index);

static inline bool isObjType(Value value, ObjType type)
{
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif // OBJECT_H
