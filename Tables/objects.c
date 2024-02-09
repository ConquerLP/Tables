#include "object.h"

static boolean equals(void* object1, void* object2);
static void* clone(void* object);
static char* toString(void* object);
static _int getHashvalue(void* object);

Object* new_Object()
{
	Object* object;
	Malloc(object, Object, 1);
	object->hashvalue = (_int)object;
	object->equals = equals;
	object->clone = clone;
	object->toString = toString;
	object->getHashvalue = getHashvalue;
	return object;
}

static boolean equals(void* object1, void* object2)
{
	CHECK(object1);
	CHECK(object2);
	return getHashvalue(object1) == getHashvalue(object2);
}

static void* clone(void* object)
{
	Object* clone = new_Object();
	updateHashValue(clone);
}

static char* toString(void* object)
{
	return "Object";
}

static _int getHashvalue(void* object)
{
	CHECK(object);
	return this(object)->hashvalue;
}

void updateHashValue(void* object)
{
	CHECK(object);
	this(object)->hashvalue = this(object)->getHashvalue(object);
}

Object* this(void* object)
{
	if(!object) return NULL;
	return *((Object**)object);
}