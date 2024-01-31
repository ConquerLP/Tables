#ifndef HASHTABLE_H

#define HASHTABLE_H

#include "macros.h"

typedef struct _Hashentry {
	void* super;
	void* key;
	void* entry;
	_int hash_value;
	struct _Hashentry* next;
}Hashentry;

typedef struct _Hashtable {
	void* super;
	_int number_of_elements;
	Hashentry** entries;
}Hashtable;

#endif // !HASHTABLE_H
