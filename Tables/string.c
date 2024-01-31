#include "string.h"

static void* clone(void* obj);
static char* toString(void* obj);
static _int getHashCode(void* obj);

String* new_string(char* text)
{
	Object* obj = new_object();
	String* string;
	Malloc(string, String, 1);
	COPY_STRING(string->string, text);
	string->object = obj;
	obj->hashvalue = getHashCode(string);

	obj->clone = clone;
	obj->getHashCode = getHashCode;
	obj->toString = toString;
	return string;
}

static void* clone(void* obj)
{
	return new_string(toString(obj));
}

static char* toString(void* obj)
{
	return ((String*)obj)->string;
}

static _int getHashCode(void* obj)
{
	char* string = ((String*)obj)->string;
	_int i = 0;
	_int hashcode = 0;
	while (string[i] != 0) {
		hashcode += string[i];
		i++;
	}
	return hashcode;
}