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
	string->clone = clone;
	string->toString = toString;
	string->getHashvalue = getHashvalue;
	
	string->append = append;
	string->setString = setString;
	
	updateHashvalue(string);
	return string;
}

static void* clone(void* object)
{
	CHEK(object);
	return new_String(toString(object));
}

static char* toString(void* object)
{
	CHEK(object);
	return ((String*)object)->string;
}

static _int getHashvalue(void* object)
{
	CHEK(object);
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
	CHEK(object);
	char* new_text;
	MERGE_STRING(new_text, toString(string), text);
	setString(string, new_text);
}

static void setString(String* string, char* new_text)
{
	CHEK(object);
	COPY_STRING(string->string, new_text);
	updateHashvalue(string);
}
