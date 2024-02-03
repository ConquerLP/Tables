#ifndef HASHTABLE_H

#define HASHTABLE_H

#include "macros.h"
#include "object.h"

typedef struct _Hashtable {
	Object* object;
	_int number_of_elements;
	_int capacity;
	float loadFactor;
	void** entries;
	void (*clear)(void* table);
	boolean (*contains)(void* table, void* value);
	boolean (*containsKey)(void* table, void* key);
	void* (*get)(void* table, void* key);
	boolean (*isEmpty)(void* table);
	void (*put)(void* table, void* key, void* value);
	void (*remove)(void* table, void* key);
	void (*replace)(void* table, void* key, void* value);
	_int (*getSize)(void* table);
}Hashtable;

Hashtable* new_Hashtable();

#endif // !HASHTABLE_H
