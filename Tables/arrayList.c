#include "arrayList.h"
#include "array.h"
#include "list.h"
#include "string.h"

static void* clone(void* object);
static char* toString(void* object);
static _int getHashvalue(void* object);

static _int getSize(void* arrayList);
static void* get(void* arrayList, _int index);
static void set(void* arrayList, void* object, _int index);
static void add(void* arrayList, void* object);
static void removeIndex (void* arrayList, _int index);
static void removeObject (void* arrayList, void* object);
static void addAllList(void* arrayList, void* list);
static void addAllArrayList(void* arrayList, void* appendingArrayList);
static void addAllArray(void* arrayList, void* array);
static boolean contains(void* arrayList, void* object);
static _int indexOf(void* arrayList, void* element);
static void* toArray(void* arrayList);

static void checkIndex(void* arrayList, _int index);

ArrayList* new_ArrayList()
{
	ArrayList* arrayList;
	Malloc(arrayList, ArrayList, 1);
	arrayList->object = new_Object();
	arrayList->size = 0;
	arrayList->elements = NULL;
	
	arrayList->getSize = getSize;
	arrayList->get = get;
	arrayList->set = set;
	arrayList->addAllList = addAllList;
	arrayList->addAllArrayList = addAllArrayList;
	arrayList->addAllArray = addAllArray;
	arrayList->contains = contains;
	arrayList->indexOf = indexOf;
	arrayList->toArray = toArray;
	
	arrayList->object->clone = clone;
	arrayList->object->toString = toString;
	arrayList->object->getHashvalue = getHashvalue;
	
	return arrayList;
}

static void* clone(void* object)
{
	CHECK(object);
	Arraylist* clone = new_ArrayList();
	for(_int i = 0; i < getSize(object); ++i){
		clone->add(clone, get(object, i));
	}
	return clone;
}

static char* toString(void* object)
{
	CHECK(object);
	String* string = new_String("");
	Object* interface = NULL;
	void* element = NULL;
	for(_int i = 0; i < getSize(object); ++i){
		element = get(object, i);
		interface = this(element);
		if(element && interface){
			string->append(string, "{ ");
			string->append(string, interface->toString(element));
			string->append(string, " }, ");
		}
	}
	return string->object->toString(string);
}

static _int getHashvalue(void* object)
{
	CHECK(object);
	_int hashvalue = 0;
	Object* interface = NULL;
	void* element = NULL;
	for(_int i = 0; i < getSize(object); ++i){
		element = get(object, i);
		interface = this(element);
		if(element && interface) hashvalue += interface->getHashvalue(element);
	}
	return hashvalue;
}

static _int getSize(void* arrayList)
{
	CHECK(arrayList);
	return ((ArrayList*)arrayList)->size;
}

static void* get(void* arrayList, _int index)
{
	CHECK(arrayList);
	if(checkIndex(arrayList, index) == INVALID_INDEX) return NULL;
	return ((ArrayList*)arrayList)->elements[index];
}

static void set(void* arrayList, void* object, _int index)
{
	CHECK(arrayList);
	CHECK(object);
	if(checkIndex(arrayList, index) == INVALID_INDEX) return;
	((ArrayList*)arrayList)->elements[index] = object;
	updateHashValue(arrayList);
}

static void add(void* arrayList, void* object)
{
	CHECK(arrayList);
	CHECK(object);
	ArrayList* arrayList_ptr = arrayList;
	arrayList_ptr->size += 1;
	Realloc(arrayList_ptr->elements, void*, arrayList_ptr->size);
	set(arrayList, object, arrayList_ptr->size - 1);
}

static void removeIndex (void* arrayList, _int index)
{
	CHECK(arrayList);
	if(checkIndex(arrayList, index) == INVALID_INDEX) return;
	void** new_elements;
	Malloc(new_elements, void*, getSize(arrayList) - 1);
	ArrayList* arrayList_ptr = arrayList;
	arrayList_ptr->elements[index] = NULL;
	void* content;
	for(_int i = 0; i < getSize(arrayList); ++i){
		content = get(arrayList, i);
		if(content){
			new_elements[i] = content;
		} 
		else {
			continue;
		}
	}
	array_ptr->elements = new_elements;
	array_ptr->size -= 1;
	updateHashValue(arrayList);
}

static void removeObject (void* arrayList, void* object)
{
	CHECK(arrayList);
	CHECK(object);
	removeIndex(arrayList, indexOf(arrayList, object));
}

static void addAllList(void* arrayList, void* list)
{
	CHECK(arrayList);
	CHECK(list);
	List* list_ptr = list;
	ArrayList* arrayList_ptr = arrayList;
	for(_int i = 0; i < list_ptr->getSize(list); ++i){
		arrayList_ptr->add(arrayList_ptr, list_ptr->get(list_ptr, i));
		arrayList_ptr->size += 1;
	}
}

static void addAllArrayList(void* arrayList, void* appendingArrayList)
{
	CHECK(arrayList);
	CHECK(appendingArrayList);
	ArrayList* appendingArrayList_ptr = appendingArrayList;
	ArrayList* arrayList_ptr = arrayList;
	for(_int i = 0; i < appendingArrayList_ptr->getSize(appendingArrayList_ptr); ++i){
		arrayList_ptr->add(arrayList_ptr, appendingArrayList_ptr->get(appendingArrayList_ptr, i));
		arrayList_ptr->size += 1;
	}
}

static void addAllArray(void* arrayList, void* array)
{
	CHECK(arrayList);
	CHECK(array);
	Array* array_ptr = array;
	ArrayList* arrayList_ptr = arrayList;
	for(_int i = 0; i < array_ptr->getSize(list); ++i){
		arrayList_ptr->add(arrayList_ptr, array_ptr->get(array_ptr, i));
		arrayList_ptr->size += 1;
	}
}
static boolean contains(void* arrayList, void* object)
{
	CHECK(arrayList);
	CHECK(object);
	Object* interface = NULL;
	void* element = NULL;
	for(_int i = 0; i < getSize(arrayList); ++i){
		element = get(arrayList, i);
		interface = this(element);
		if(interface && element && interface->equals(element, object)) return true;
	}
	return false;
}

static _int indexOf(void* arrayList, void* object)
{
	CHECK(arrayList);
	CHECK(object);
	Object* interface = NULL;
	void* element = NULL;
	for(_int i = 0; i < getSize(arrayList); ++i){
		element = get(arrayList, i);
		interface = this(element);
		if(interface && element && interface->equals(element, object)) return i;
	}
	return INVALID_INDEX;
}

static void* toArray(void* arrayList)
{
	CHECK(arrayList);
	Array* array = new_Array(getSize(arrayList));
	for(_int i = 0; i < getSize(arrayList); ++i){
		array->set(array, arrayList->get(arrayList, i), i);
	}
	return array;
}

static void checkIndex(void* arrayList, _int index)
{
	CHECK(list);
	if(index == INVALID_INDEX) return;
	if(index >= getSize(arrayList)) ERROR("Index out of bounds arrayList.");
}
