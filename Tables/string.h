#ifndef STRING_H

#define STRING_H

#include "object.h"

typedef struct _String {
	Object* object;
	char* string;
}String;

String* new_string(char* text);

#endif // !STRING_H
