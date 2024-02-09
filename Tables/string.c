#include "string.h"

static void* clone(void* object);
static char* toString(void* object);
static _int getHashvalue(void* object);

static void append(void* string, char* text);
static void setString(String* string, char* new_text);

String* new_String(char* text)
{
	String* string;
	Malloc(string, String, 1);
	string->object = new_Object();
	COPY_STRING(string->string, text);
	string->object->clone = clone;
	string->object->toString = toString;
	string->object->getHashvalue = getHashvalue;
	
	string->append = append;
	string->setString = setString;
	
	updateHashValue(string);
	return string;
}

static void* clone(void* object)
{
	CHECK(object);
	return new_String(toString(object));
}

static char* toString(void* object)
{
	CHECK(object);
	return ((String*)object)->string;
}

static _int getHashvalue(void* object)
{
	CHECK(object);
	char* string = toString(object);
	_int i = 0;
	_int hashvalue = 0;
	while(string[i] != 0){
		hashvalue *= 10;
		hashvalue += string[i];
		++i;
	}
	return hashvalue;
}

static void append(void* string, char* text)
{
	CHECK(string);
	char* new_text;
	MERGE_STRING(new_text, toString(string), text);
	setString(string, new_text);
}

static void setString(String* string, char* new_text)
{
	CHECK(string);
	COPY_STRING(string->string, new_text);
	updateHashValue(string);
}
