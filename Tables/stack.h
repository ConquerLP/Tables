#ifndef STACK_H

#define STACK_H

#include "object.h"

typedef struct _Stack{
	Object* object;
	void** elements;
	_int stackSize;
	_int stackPtr;
	void* (*peek)(void* stack);
	void* (*pop)(void* stack);
	void (*push)(void* stack, void* toPush);
	_int (*search)(void* stack, void* toSearch);
}Stack;

Stack* new_Stack(_int stackSize);

#endif