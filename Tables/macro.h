#ifndef MACRO_H

#define MACRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
#define boolean char
#define _int size_t

#define Malloc(ptr, type, amount) ptr = malloc(sizeof(type) * (amount)); if(!ptr) { fprintf(stderr, "Could not allocate memory. In File: \n%s\nIn Line: %i", __FILE__, __LINE__); exit(1);}
#define CHECK(ptr) if(!ptr) { fprintf(stderr, "Nullpointer. In File: \n%s\nIn Line: %i", __FILE__, __LINE__); exit(1); }
#define BOOL_STRING(expression) (expression) ? "true" : "false"
#define ARRAY_SIZE(ptr) (sizeof((ptr)) / sizeof((*ptr)))
#define COPY_STRING(dest, src) Malloc(dest, char, strlen(src) + 1); strcpy(dest, src);
#define MERGE_STRING(dest, src1, src2) Malloc(dest, char, strlen(src1) + strlen(src2) + 1); strcpy(dest, src1); strcat(dest, src2);
#define ERROR(msg) { fprintf(stderr, "%s", msg); exit(1); }
#define Realloc(ptr, type, amount) ptr = realloc(ptr, sizeof(type) * (amount)); if(!ptr) { fprintf(stderr, "Could not allocate memory. In File: \n%s\nIn Line: %i", __FILE__, __LINE__); exit(1); }
#define CHAR_TO_STRING(c) #c

#endif