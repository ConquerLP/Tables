#include "string.h"

static void* clone(void* obj);
static char* toString(void* obj);
static _int getHashCode(void* obj);

static void append(void* string, char* appending_text);
static void set(void* string, char* new_text);

String* new_String(char* text)
{
	CHECK(text);
	String* string;
	Malloc(string, String, 1);
	COPY_STRING(string->string, text);
	string->object = new_Object();
	string->object->hashvalue = getHashCode(string);
	string->object->clone = clone;
	string->object->getHashCode = getHashCode;
	string->object->toString = toString;

	string->append = append;
	string->set = set;
	return string;
}

static void* clone(void* obj)
{
	return new_String(toString(obj));
}

static char* toString(void* obj)
{
	return ((String*)obj)->string;
}

static _int getHashCode(void* obj)
{
	char* string = toString(obj);
	_int i = 0;
	_int hashcode = 0;
	while (string[i] != 0) {
		hashcode += string[i];
		i++;
	}
	return hashcode;
}

static void append(void* string, char* appending_text)
{
	CHECK(string);
	char* merged;
	MERGE_STRING(merged, toString(string), appending_text);
	set(string, merged);
}

static void set(void* string, char* new_text)
{
	CHECK(string);
	CHECK(new_text);
	COPY_STRING(((String*)string)->string, new_text);
}