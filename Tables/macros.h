#ifndef MACROS_H

#define MACROS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define ARRAY_SIZE(ptr) (sizeof((ptr)) / sizeof((*ptr)))
#define true 1
#define false 0
#define boolean char
#define _int size_t
#define null NULL

#define ERROR(msg) { fprintf(stderr, "%s", msg); exit(1); }
#define CHECK(ptr) if(!ptr) { fprintf(stderr, "Nullpointer in file: %s\nLine: %i", __FILE__, __LINE__); exit(1); }
#define Malloc(ptr, type, amount) ptr = malloc(sizeof(type) * (amount)); CHECK(ptr);
#define Realloc(ptr, type, amount) ptr = realloc(ptr, sizeof(type) * (amount)); CHECK(ptr);
#define COPY_STRING(dest, src)  { CHECK(src); Malloc(dest, char, strlen(src) + 1); memset(dest, 0, strlen(src) + 1); strcpy(dest, src); }
#define MERGE_STRING(dest, str1, str2) { CHECK(str1); CHECK(str2); \
		Malloc(dest, char, strlen(str1) + strlen(str2) + 1); memset(dest, 0, strlen(str1) + strlen(str2) + 1); \
		strcat(dest, str1); strcat(dest, str2); }
#define APPEND_STRING(str, appender) { Realloc(str, char, strlen(str) + strlen(appender) + 1); \
		memset(str + strlen(str) + 1, 0, strlen(appender) + 1); strcat(str, appender); }
#define BOOLEAN_STRING(expression) (expression) ? "true" : "false"
#define CAST_TO_OBJECT(work_ptr, ptr) work_ptr = (*(Object**)ptr)

#endif // !MACROS_H
