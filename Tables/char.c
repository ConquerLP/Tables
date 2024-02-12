#include "char.h"
#include "string.h"

static void* clone(void* object);
static char* toString(void* object);
static _int getHashvalue(void* object);

static char charValue(void* object);
static boolean isDigit(void* object);
static boolean isAlpha(void* object);
static boolean isAlphaNum(void* object);
static boolean isLowerCase(void* object);
static boolean isUpperCase(void* object);
static char toLowerCase(void* object);
static char toUpperCase(void* object);

Char* new_Char(char character)
{
	Char* c;
	Malloc(c, Char, 1);
	c->object = new_Object();
	c->object->clone = clone;
	c->object->getHashvalue = getHashvalue;
	c->object->toString = toString;
	c->character = character;
	c->charValue = charValue;
	c->isDigit = isDigit;
	c->isAlpha = isAlpha;
	c->isAlphaNum = isAlphaNum;
	c->isLowerCase = isLowerCase;
	c->isUpperCase = isUpperCase;
	c->toLowerCase = toLowerCase;
	c->toUpperCase = toUpperCase;
	updateHashValue(c);
	return c;
}

static void* clone(void* object)
{
	CHECK(object);
	return new_Char(charValue(object));
}

static char* toString(void* object)
{
	CHECK(object);
	String* string = new_StringChar(charValue(object));
	return string->object->toString(string);
}

static _int getHashvalue(void* object)
{
	CHECK(object);
	return (_int)charValue(object);
}

static char charValue(void* object)
{
	CHECK(object);
	return ((Char*)object)->character;
}

static boolean isDigit(void* object)
{
	CHECK(object);
	return charValue(object) > 47 && charValue(object) < 58;
}

static boolean isAlpha(void* object)
{
	CHECK(object);
	char c = charValue(object);
	return isUpperCase(object) || isLowerCase(object);
}

static boolean isAlphaNum(void* object)
{
	CHECK(object);
	return isAlpha(object) || isDigit(object);
}

static boolean isLowerCase(void* object)
{
	CHECK(object);
	return charValue(object) > 96 && charValue(object) < 123;
}

static boolean isUpperCase(void* object)
{
	CHECK(object);
	return charValue(object) > 64 && charValue(object) < 91;
}

static char toLowerCase(void* object)
{
	CHECK(object);
	if (isAlpha(object)) {
		if (isLowerCase(object)) return charValue(object);
		else return charValue(object) + 32;
	} 
	return charValue(object);
}

static char toUpperCase(void* object)
{
	CHECK(object);
	if (isAlpha(object)) {
		if (isUpperCase(object)) return charValue(object);
		else return charValue(object) - 32;
	}
	return charValue(object);
}
