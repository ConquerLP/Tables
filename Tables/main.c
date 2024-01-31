#include "std_lib.h"

int main(void) {

	String* string = new_string("test");
	String* copy = string->object->clone(string);
	printf("%s", BOOLEAN_STRING(string->object->equals(string, copy)));


	return 0;
}