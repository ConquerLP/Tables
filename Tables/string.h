#ifndef STRING_H

#define STRING_H

#include "object.h"

typedef struct _String{
	Object* object;
	char* string;
	void (*append)(void* string, char* text);
	void (*setString)(void* string, char* new_text);
}String;

String* new_String(char* text);
String* new_StringChar(char c);

#endif