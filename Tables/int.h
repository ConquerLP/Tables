#ifndef INT_H

#define INT_H

#include "object.h"

typedef struct _Int {
	Object* object;
	int value;
}Int;

Int* new_Int(int value);

#endif // !INT_H
