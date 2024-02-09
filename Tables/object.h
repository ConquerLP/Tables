#ifndef OBJECT_H

#define OBJECT_H

#include "macro.h"

#define INVALID_INDEX -1

typedef struct _Object{
	_int hashvalue;
	boolean (*equals)(void* object1, void* object2);
	void* (*clone)(void* object);
	char* (*toString)(void* object);
	_int (*getHashvalue)(void* object);
}Object;

Object* new_Object();
Object* this(void* object);
void updateHashValue(void* object);

#endif