#include "hashtable.h"

#define INTIAL_CAPACITY 11
#define LOAD_FACTOR 0.75

typedef struct _Hashentry {
	void* key;
	void* value;
	struct _Hashentry* next;
}Hashentry;

static Hashentry* new_Hashentry(void* key, void* value);

static void* clone(void* obj);
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
static _int getSize(void* table);

static void rehash(void* table);

static Hashentry* new_Hashentry(void* key, void* value)
{
	Hashentry* entry;
	Malloc(entry, Hashentry, 1);
	entry->key = key;
	entry->value = value;
	entry->next = NULL;
	return entry;
}

Hashtable* new_Hashtable()
{
	Hashtable* table;
	Malloc(table, Hashtable, 1);
	table->object = new_Object();
	table->number_of_elements = 0;
	table->capacity = INTIAL_CAPACITY;
	table->loadFactor = LOAD_FACTOR;
	Malloc(table->entries, void*, INTIAL_CAPACITY);
	for (_int i = 0; i < INTIAL_CAPACITY; ++i) {
		table->entries[i] = NULL;
	}
	table->object->clone = clone;
	table->object->getHashCode = getHashCode;
	table->object->toString = toString;
	table->clear = clear;
	table->contains = contains;
	table->containsKey = containsKey;
	table->get = get;
	table->isEmpty = isEmpty;
	table->put = put;
	table->remove = remove;
	table->replace = replace;
	table->getSize = getSize;
	return table;
}

static void clear(void* table)
{
	CHECK(table);
	Hashtable* table_ptr = table;
	for (_int i = 0; i < table_ptr->capacity; ++i) {
		table_ptr->entries[i] = NULL;
	}
	table_ptr->entries = NULL;
	table_ptr->capacity = 0;
	table_ptr->number_of_elements = 0;
}

static boolean contains(void* table, void* value);
static boolean containsKey(void* table, void* key);
static void* get(void* table, void* key);

static boolean isEmpty(void* table)
{
	CHECK(table);
	return ((Hashtable*)table)->number_of_elements;
}

static void put(void* table, void* key, void* value);
static void remove(void* table, void* key);
static void replace(void* table, void* key, void* value);
static _int getSize(void* table);

static void rehash(void* table);