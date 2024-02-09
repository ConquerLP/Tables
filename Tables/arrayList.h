#ifndef ARRAY_LIST

#define ARRAY_LIST

#include "object.h"

typedef struct _ArrayList{
	Object* object;
	_int size;
	void** elements;
	_int (*getSize)(void* arrayList);
	void* (*get)(void* arrayList, _int index);
	void (*set)(void* arrayList, void* object, _int index);
	void (*add)(void* arrayList, void* object);
	void (*removeIndex)(void* arrayList, _int index);
	void (*removeObject)(void* arrayList, void* object);
	void (*addAllList)(void* arrayList, void* list);
	void (*addAllArrayList)(void* arrayList, void* appendingArrayList);
	void (*addAllArray)(void* arrayList, void* array);
	boolean (*contains)(void* arrayList, void* object);
	_int (*indexOf)(void* arrayList, void* object);
	void* (*toArray)(void* arrayList);
}ArrayList;

ArrayList* new_ArrayList();

#endif