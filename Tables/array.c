#include "array.h"
#include "string.h"

static void* clone(void* obj);
static char* toString(void* obj);
static _int getHashCode(void* obj);

static _int getSize(void* array);
static void* get(void* array, _int index);
static void set(void* array, void* element, _int index);

Array* new_Array(_int size)
{
	if (size <= 0) ERROR("Array size is 0 or negative.");
	Array* array;
	Malloc(array, Array, 1);
	array->object = new_Object();
	array->size = size;
	void** elements;
	Malloc(elements, void*, size);
	array->elements = elements;
	array->getSize = getSize;
	array->get = get;
	array->set = set;
	array->object->clone = clone;
	array->object->toString = toString;
	array->object->getHashCode = getHashCode;
	return array;
}

static void* clone(void* obj)
{
	CHECK(obj);
	Array* clone = new_Array(getSize(obj));
	for (_int i = 0; i < getSize(obj); ++i) {
		clone->set(clone, get(obj, i), i);
	}
	return clone;
}

static char* toString(void* obj)
{
	CHECK(obj);
	Array* array_ptr = obj;
	Object* object_ptr;
	String* string = new_String("");
	for (_int i = 0; i < getSize(obj); ++i) {
		object_ptr = get(obj, i);
		string->append(string, "{ ");
		string->append(string, object_ptr->toString(object_ptr));
		string->append(string, " }, ");
	}
	return string->object->toString(string);
}

static _int getHashCode(void* obj)
{
	CHECK(obj);
	_int hashvalue = 0;
	Object* object_ptr;
	for (_int i = 0; i < getSize(obj); ++i) {
		object_ptr = get(obj, i);
		hashvalue += object_ptr->getHashCode(object_ptr);
	}
	return hashvalue;
}

static _int getSize(void* array)
{
	CHECK(array);
	return ((Array*)array)->size;
}

static void* get(void* array, _int index)
{
	CHECK(array);
	if (index >= getSize(array)) ERROR("Index out of bounds array.");
	return ((Array*)array)->elements[index];
}

static void set(void* array, void* element, _int index)
{
	CHECK(array);
	CHECK(element);
	if (index >= getSize(array)) ERROR("Index out of bounds array.");
	((Array*)array)->elements[index] = element;
}
