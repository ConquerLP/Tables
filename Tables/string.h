#ifndef STRING_H

#define STRING_H

#include "object.h"

typedef struct _String {
	Object* object;
	char* string;
	void (*set)(void* string, char* new_text);
	void (*append)(void* string);
}String;

String* new_String(char* text);

#endif // !STRING_H
