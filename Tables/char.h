#ifndef CHAR_H

#define CHAR_H

#include "object.h"

typedef struct _Char {
	Object* object;
	char character;
	char (*charValue)(void* object);
	boolean	(*isDigit)(void* object);
	boolean	(*isAlpha)(void* object);
	boolean	(*isAlphaNum)(void* object);
	boolean	(*isLowerCase)(void* object);
	boolean	(*isUpperCase)(void* object);
	char (*toLowerCase)(void* object);
	char (*toUpperCase)(void* object);
}Char;

Char* new_Char(char character);

#endif // !CHAR_H
