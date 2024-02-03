#ifndef OBJECT_H

#define OBJECT_H

#include "macros.h"

typedef struct _Object {
	_int hashvalue;
	void* (*clone)(void* obj);
	boolean (*equals)(void* obj1, void* obj2);
	char* (*toString)(void* obj);
	_int (*getHashCode)(void* obj);
}Object;

Object* new_Object();

#endif // !OBJECT_H
