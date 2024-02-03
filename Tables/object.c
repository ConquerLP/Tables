#include "object.h"

static void* clone(void* obj);
static boolean equals(void* obj1, void* obj2);
static char* toString(void* obj);
static _int getHashCode(void* obj);

Object* new_Object()
{
	Object* object;
	Malloc(object, Object, 1);
	object->clone = clone;
	object->equals = equals;
	object->toString = toString;
	object->getHashCode = getHashCode;
	object->hashvalue = (_int)object;
	return object;
}

static void* clone(void* obj)
{
	Object* clone = new_Object();
	clone->hashvalue = getHashCode(obj);
	return clone;
}

static boolean equals(void* obj1, void* obj2)
{
	return getHashCode(obj1) == getHashCode(obj2);
}
static char* toString(void* obj)
{
	return "object";
}

static _int getHashCode(void* obj)
{
	return (*(Object**)obj)->hashvalue;
}