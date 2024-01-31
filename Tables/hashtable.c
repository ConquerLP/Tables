#include "hashtable.h"

#define INTIAL_CAPACITY 11
#define LOAD_FACTOR 0.75

typedef struct _Hashentry {
	void* key;
	void* value;
	struct _Hashentry* next;
}Hashentry;

static void* clone(void* obj);
static boolean equals(void* obj1, void* obj2);
static char* toString(void* obj);
static _int getHashCode(void* obj);

static void clear(void* table);
static boolean contains(void* table, void* value);
static boolean containsKey(void* table, void* key);
static void* get(void* table, void* key);
static boolean isEmpty(void* table);
static void put(void* table, void* key, void* value);
static void remove(void* table, void* key);
static void replace(void* table, void* key, void* value);
static _int size(void* table);

static void rehash(void* table);

Hashtable* new_Hashtable()
{
	Hashtable* table;
	Malloc(table, Hashtable, 1);
	table->object = new_object();
	table->number_of_elements = 0;
	table->capacity = INTIAL_CAPACITY;
	table->loadFactor = LOAD_FACTOR;



}
