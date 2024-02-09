#ifndef HASHTABLE_H

#define HASHTABLE_H

#include "object.h"

#define LOADFACTOR 0.75
#define INTIAL_CAPACITY 11

typedef struct _Hashtable{
	Object* object;
	_int numberOfElements;
	_int capacity;
	double loadfactor;
	void** entries;
	void (*clear)(void* hashstable);
	boolean (*containsValue)(void* hashstable, void* value);
	boolean (*containsKey)(void* hashstable, void* key);
	void* (*get)(void* hashstable, void* key);
	boolean (*isEmpty)(void* hashstable);
	void (*put)(void* hashstable, void* key, void* value);
	void (*putIfAbsent)(void* hashstable, void* key, void* value);
	void (*removeByKey)(void* hashstable, void* key);
	void (*removeByKeyAndValue)(void* hashstable, void* key, void* value);
	void (*replaceByKey)(void* hashtable, void* key, void* newValue);
	void (*replaceByKeyAndValue)(void* hashtable, void* key, void* value, void* newValue);
	_int (*getSize)(void* hashtable);
	void (*rehash)(void* hashtable);
}Hashtable;

Hashtable* new_HashtableDefault();
Hashtable* new_Hashtable(double loadfactor, _int initialCapacity);

#endif