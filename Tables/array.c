#include "array.h"
#include "string.h"

static void* clone(void* object);
static char* toString(void* object);
static _int getHashvalue(void* object);

static _int getSize(void* array);
static void set(void* array, void* element, _int index);
static void* get(void* array, _int index);

static void checkIndex(void* array, _int index);

Array* new_Array(_int size)
{
	if(size <= 0) ERROR("Invalid array size.");
	Array* array;
	Malloc(array, Array, 1);
	array->object = new_Object();
	array->size = size;
	void** elements;
	Malloc(elements, void*, size);
	array->elements = elements;
	for(_int i = 0; i < size; ++i){
		elements[i] = NULL;
	}
	array->getSize = getSize;
	array->set = set;
	array->get = get;
	array->object->clone = clone;
	array->object->toString = toString;
	array->object->getHashvalue = getHashvalue;
	updateHashValue(array);
	return array;
}

static void* clone(void* object)
{
	CHECK(object);
	Array* clone = new_Array(getSize(object));
	for(_int i = 0; i < getSize(object); ++i){
		clone->set(clone, get(object, i), i);
	}
	return clone;
}

static char* toString(void* object)
{
	CHECK(object);
	String* string = new_String("");
	Object* interface = NULL;
	void* element = NULL;
	for(_int i = 0; i < getSize(object); ++i){
		element = get(object, i);
		interface = this(element);
		if(element && interface){
			string->append(string, "{ ");
			string->append(string, interface->toString(element));
			string->append(string, " }, ");
		}
	}
	return string->object->toString(string);
}

static _int getHashvalue(void* object)
{
	CHECK(object);
	_int hashvalue = 0;
	Object* interface = NULL;
	void* element = NULL;
	for(_int i = 0; i < getSize(object); ++i){
		element = get(object, i);
		interface = this(element);
		if(element && interface) hashvalue += interface->getHashvalue(element);
	}
	return hashvalue;
}

static _int getSize(void* array)
{
	CHECK(array);
	return ((Array*)array)->size;
}

static void set(void* array, void* element, _int index)
{
	CHECK(array);
	CHECK(element);
	checkIndex(array, index);
	((Array*)array)->elements[index] = element;
	updateHashValue(array);
}

static void* get(void* array, _int index)
{
	CHECK(array);
	checkIndex(array, index);
	return ((Array*)array)->elements[index];
}

static void checkIndex(void* array, _int index)
{
	CHECK(array);
	if(index < 0 || index >= getSize(array)) ERROR("Index out of bounds array.");
}