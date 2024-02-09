#ifndef LIST_H

#define LIST_H

#include "object.h"

typedef struct _List{
	Object* object;
	void* start;
	_int size;
	void (*add)(void* list, void* object);
	void (*addAfter) (void* list, void* object, _int index);
	void (*addBefore) (void* list, void* object, _int index);
	void (*addAllList)(void* list, void* anotherList);
	void (*addAllArray)(void* list, void* array);
	void (*addAllArrayList)(void* list, void* arrayList);
	void (*clear)(void* list);
	boolean (*contains)(void* list, void* object);
	void* (*get)(void* list, _int index);
	_int (*indexOf)(void* list, void* object);
	boolean (*isEmpty)(void* list);
	_int (*getSize)(void* list);
	void (*removeIndex)(void* list, _int index);
	void (*removeObject)(void* list, void* object);
	void (*replaceIndex)(void* list, void* replacement, _int index);
	void (*replaceObject)(void* list, void* object, void* replacement);
	struct _List* (*sublist)(void* list, _int startIndex, _int endIndex);
	void* (*toArray)(void* list);
}List;

List* new_List();

#endif