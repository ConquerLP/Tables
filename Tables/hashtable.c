#include "hashtable.h"
#include "string.h"

typedef struct _Hashentry {
	void* key;
	void* value;
	struct Hashentry* next;
	struct Hashentry* prev;
}Hashentry;

static void* getKey(Hashentry* entry);
static void* getValue(Hashentry* entry);

static void* clone(void* object);
static char* toString(void* object);
static _int getHashvalue(void* object);

static void clear(void* hashtable);
static boolean containsValue(void* hashtable, void* value);
static boolean containsKey(void* hashtable, void* key);
static void* get(void* hashtable, void* key);
static boolean isEmpty(void* hashtable);
static void put(void* hashtable, void* key, void* value);
static void putIfAbsent(void* hashtable, void* key, void* value);
static void removeByKey(void* hashtable, void* key);
static void removeByKeyAndValue(void* hashtable, void* key, void* value);
static void replaceByKey(void* hashtable, void* key, void* newValue);
static void replaceByKeyAndValue(void* hashtable, void* key, void* value, void* newValue);
static _int getSize(void* hashtable);
static void rehash(void* hashtable);

static void resize(void* hashtable, _int capacity);
static _int calcIndex(void* hashtable, void* key);

Hashtable* new_HashtableDefault()
{
	Hashtable* table;
	Malloc(table, Hashtable, 1);
	table->object = new_Object();
	table->numberOfElements = 0;
	table->capacity = INTIAL_CAPACITY;
	table->loadfactor = LOADFACTOR;
	Malloc(table->entries, Hashentry*, INTIAL_CAPACITY);
	for(_int i = 0; i < INTIAL_CAPACITY; ++i){
		table->entries[i] = NULL;
	}
	table->object->clone = clone;
	table->object->toString = toString;
	table->object->getHashvalue = getHashvalue;
	table->clear = clear;
	table->containsValue = containsValue;
	table->containsKey = containsKey;
	table->get = get;
	table->isEmpty = isEmpty;
	table->put = put;
	table->putIfAbsent = putIfAbsent;
	table->removeByKey = removeByKey;
	table->removeByKeyAndValue = removeByKeyAndValue;
	table->replaceByKey = replaceByKey;
	table->replaceByKeyAndValue = replaceByKeyAndValue;
	table->getSize = getSize;
	table->rehash = rehash;
	updateHashValue(table);
	return table;
}

Hashtable* new_Hashtable(double loadfactor, _int initialCapacity)
{
	if(loadfactor <= 0.0) ERROR("loadfactor must be positive hashtable.");
	if(initialCapacity <= 0) ERROR("Initalcapacity must be positive hashtable.");
	Hashtable* table = new_HashtableDefault();
	table->loadfactor = loadfactor;
	table->capacity = initialCapacity;
	Malloc(table->entries, Hashentry*, initialCapacity);
	for(_int i = 0; i < initialCapacity; ++i){
		table->entries[i] = NULL;
	}
	updateHashValue(table);
	return table;
}

static void* clone(void* object)
{
	CHECK(object);
	Hashtable* hashtable_ptr = object;
	Hashtable* clone = new_Hashtable(hashtable_ptr->loadfactor, hashtable_ptr->capacity);
	for(_int i = 0; i < hashtable_ptr->numberOfElements; ++i){
		clone->entries[i] = hashtable_ptr->entries[i];
	}
	updateHashValue(object);
	return clone;
}

static char* toString(void* object)
{
	CHECK(object);
	String* string = new_String("");
	Hashtable* hashtable_ptr = object;
	Object* interface = NULL;
	Object* key_interface = NULL;
	Object* value_interface = NULL;
	void* key = NULL;
	void* value = NULL;
	Hashentry* entry = NULL;
	for(_int i = 0; i < hashtable_ptr->capacity; ++i){
		entry = hashtable_ptr->entries[i];
		if(entry){
			while(entry != NULL){
				key = getKey(entry);
				value = getValue(entry);
				key_interface = this(key);
				value_interface = this(value);
				if(key && value && key_interface && value_interface){
					string->append(string, "{ Key: ");
					string->append(string, key_interface->toString(key));
					string->append(string, " Value: ");
					string->append(string, value_interface->toString(value));
					string->append(string, " }, ");
				}
				entry = entry->next;
			}
		}
		entry = NULL;
	}
	return string->object->toString(string);
}

static _int getHashvalue(void* object)
{
	CHECK(object);
	return (_int)((Hashtable*)object)->entries;
}

static void clear(void* hashtable)
{
	CHECK(hashtable);
	Hashtable* hashtable_ptr = hashtable;
	hashtable_ptr->numberOfElements = 0;
	for (_int i = 0; i < hashtable_ptr->capacity; ++i) {
		hashtable_ptr->entries[i] = NULL;
	}
}

static boolean containsValue(void* hashtable, void* value)
{}
static boolean containsKey(void* hashtable, void* key)
{}
static void* get(void* hashtable, void* key)
{
	
	
	
}

static boolean isEmpty(void* hashtable)
{
	CHECK(hashtable);
	if(getSize(hashtable) == 0) return true;
	else return false;
}

static void put(void* hashtable, void* key, void* value)
{}
static void putIfAbsent(void* hashtable, void* key, void* value)
{}
static void removeByKey(void* hashtable, void* key)
{}
static void removeByKeyAndValue(void* hashtable, void* key, void* value)
{}
static void replaceByKey(void* hashtable, void* key, void* newValue)
{}
static void replaceByKeyAndValue(void* hashtable, void* key, void* value, void* newValue)
{}
static _int getSize(void* hashtable)
{
	CHECK(hashtable);
	return ((Hashtable*)hashtable)->numberOfElements;
	
}

static void rehash(void* hashtable)
{}

static void resize(void* hashtable, _int capacity)
{}
static _int calcIndex(void* hashtable, void* key)
{
	CHECK(hashtable);
	CHECK(key);
	Hashtable* hashtable_ptr = hashtable;
	Object* interface = this(key);
	if (interface)return interface->getHashvalue(key) % hashtable_ptr->capacity;
	else return INVALID_INDEX;
}

static void* getKey(Hashentry* entry)
{}
static void* getValue(Hashentry* entry)
{}