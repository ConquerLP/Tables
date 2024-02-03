#ifndef ARRAY_H

#define ARRAY_H

#include "object.h"

typedef struct _Array {
	Object* object;
	_int size;
	void** elements;
	_int (*getSize)(void* array);
	void* (*get)(void* array, _int index);
	void (*set)(void* array, void* element, _int index);
}Array;

Array* new_Array(_int size);

#endif // !ARRAY_H
