#include "list.h"
#include "string.h"
#include "arrayList.h"
#include "array.h"
#include "node.h"

static void* clone(void* object);
static char* toString(void* object);
static _int getHashvalue(void* object);

static void add (void* list, void* object);
static void addAfter (void* list, void* object, _int index);
static void addBefore (void* list, void* object, _int index);
static void addAllList (void* list, void* anotherList);
static void addAllArray (void* list, void* array);
static void addAllArrayList (void* list, void* arrayList);
static void clear (void* list);
static boolean contains (void* list, void* object);
static void* get (void* list, _int index);
static _int indexOf (void* list, void* object);
static boolean isEmpty (void* list);
static _int getSize (void* list);
static void removeIndex (void* list, _int index);
static void removeObject (void* list, void* object);
static void replaceIndex (void* list, void* replacement, _int index);
static void replaceObject (void* list, void* object, void* replacement);
static struct _List* sublist(void* list, _int startIndex, _int endIndex);
static void* toArray (void* list);

static _int checkIndex(void* list, _int index);
static Node* getStartNode(void* list);

List* new_List()
{
	List* list;
	Malloc(list, List, 1);
	list->object = new_Object();
	list->start = NULL;
	list->size = 0;
	list->add = add;
	list->addBefore = addBefore;
	list->addAfter = addAfter;
	list->addAllList = addAllList;
	list->addAllArrayList = addAllArrayList;
	list->addAllArray = addAllArray;
	list->clear = clear;
	list->contains = contains;
	list->get = get;
	list->indexOf = indexOf;
	list->isEmpty = isEmpty;
	list->getSize = getSize;
	list->removeIndex = removeIndex;
	list->removeObject = removeObject;
	list->replaceIndex = replaceIndex;
	list->replaceObject = replaceObject;
	list->sublist = sublist;
	list->toArray = toArray;
	
	list->object->clone = clone;
	list->object->toString = toString;
	list->object->getHashvalue = getHashvalue;
	updateHashValue(list);
	return list;
}

static void* clone(void* object)
{
	CHECK(object);
	List* clone = new_List();
	for(_int i = 0; i < getSize(object); ++i){
		clone->add(clone, get(object, i));
	}
	updateHashValue(clone);
	return clone;
}

static char* toString(void* object)
{
	CHECK(object);
	String* string = new_String("");
	Object* element;
	for(_int i = 0; i < getSize(object); ++i){
		element = this(get(object, i));
		if(element){
			string->append(string, "{ ");
			string->append(string, element->toString(element));
			string->append(string, " }, ");
		}
	}
	return string->object->toString(string);
}

static _int getHashvalue(void* object)
{
	CHECK(object);
	_int hashvalue = 0;
	Object* value = this(object);
	for(_int i = 0; i < getSize(object); ++i){
		value = this(get(object, i));
		if(value) hashvalue += value->getHashvalue(value);
	}
	return hashvalue;
}

static void add (void* list, void* object)
{
	CHECK(list);
	CHECK(object);
	List* list_ptr = list;
	if(isEmpty(list)){
		list_ptr->start = new_Node(object);
	} 
	else {
		node_insert_after(node_get_N(getStartNode(list), getSize(list) - 1), new_Node(object));
	}
	list_ptr->size += 1;
	updateHashValue(list);
}

static void addAfter (void* list, void* object, _int index)
{
	CHECK(list);
	CHECK(object);
	List* list_ptr = list;
	if(checkIndex(list, index) == INVALID_INDEX) return;
	node_insert_after(node_get_N(getStartNode(list), index), new_Node(object));
	list_ptr->size += 1;
	updateHashValue(list);
}

static void addBefore (void* list, void* object, _int index)
{
	CHECK(list);
	CHECK(object);
	List* list_ptr = list;
	if(checkIndex(list, index) == INVALID_INDEX) return;
	node_insert_before(node_get_N(getStartNode(list), index), new_Node(object));
	list_ptr->size += 1;
	updateHashValue(list);
}

static void addAllList (void* list, void* anotherList)
{
	CHECK(list);
	CHECK(anotherList);
	List* anotherList_ptr = anotherList;
	for(_int i = 0; i < anotherList_ptr->getSize(anotherList_ptr); ++i){
		add(list, anotherList_ptr->get(anotherList_ptr, i));
	}
}

static void addAllArray (void* list, void* array)
{
	CHECK(list);
	CHECK(array);
	Array* array_ptr = array;
	for(_int i = 0; i < array_ptr->getSize(array_ptr); ++i){
		add(list, array_ptr->get(array_ptr, i));
	}
}

static void addAllArrayList (void* list, void* arrayList)
{
	CHECK(list);
	CHECK(arrayList);
	ArrayList* arrayList_ptr = arrayList;
	for(_int i = 0; i < arrayList_ptr->getSize(arrayList_ptr); ++i){
		add(list, arrayList_ptr->get(arrayList_ptr, i));
	}
}

static void clear (void* list)
{
	CHECK(list);
	List* list_ptr = list;
	list_ptr->size = 0;
	list_ptr->start = NULL;
	updateHashValue(list);
}

static boolean contains (void* list, void* object)
{
	CHECK(list);
	CHECK(object);
	if(indexOf(list, object) == INVALID_INDEX) return false;
	else return true;
}

static void* get (void* list, _int index)
{
	CHECK(list);
	if(checkIndex(list, index) == INVALID_INDEX) return NULL;
	return node_get(node_get_N(getStartNode(list), index));
}

static _int indexOf (void* list, void* object)
{
	CHECK(list);
	CHECK(object);
	Object* interface = NULL;
	void* element = NULL;
	for(_int i = 0; i < getSize(list); ++i){
		element = get(list, i);
		interface = this(element);
		if(!(interface && element)) continue;
		if(interface->equals(element, object)) return i;
	}
	return INVALID_INDEX;
}

static boolean isEmpty (void* list)
{
	CHECK(list);
	if(getSize(list) == 0) return true;
	else return false;
}

static _int getSize (void* list)
{
	CHECK(list);
	return ((List*)list)->size;
}

static void removeIndex (void* list, _int index)
{
	CHECK(list);
	if(checkIndex(list, index) == INVALID_INDEX) return;
	List* list_ptr = list;
	node_pop(getStartNode(list), index);
	list_ptr->size -= 1;
	updateHashValue(list);
}

static void removeObject (void* list, void* object)
{
	CHECK(list);
	CHECK(object);
	removeIndex(list, indexOf(list, object));
}

static void replaceIndex (void* list, void* replacement, _int index)
{
	CHECK(list);
	CHECK(replacement);
	if(checkIndex(list, index) == INVALID_INDEX) return;
	node_replace_N(getStartNode(list), replacement, index);
	updateHashValue(list);
}

static void replaceObject (void* list, void* object, void* replacement)
{
	CHECK(list);
	CHECK(object);
	replaceIndex(list, replacement, indexOf(list, object));
}

static struct _List* sublist (void* list, _int startIndex, _int endIndex)
{
	CHECK(list);
	if(startIndex >= endIndex) return NULL;
	if(checkIndex(list, startIndex) == INVALID_INDEX) return NULL;
	if(checkIndex(list, endIndex) == INVALID_INDEX) return NULL;
	List* sublist = new_List();
	for(_int i = startIndex; i < endIndex; ++i){
		sublist->add(sublist, get(list, i));
	}
	return sublist;
}

static void* toArray (void* list)
{
	CHECK(list);
	Array* array = new_Array(getSize(list));
	for(_int i = 0; i < getSize(list); ++i){
		array->set(array, get(list, i), i);
	}
	return (void*)array;
}


static _int checkIndex(void* list, _int index)
{
	CHECK(list);
	if(index == INVALID_INDEX) return INVALID_INDEX;
	if(index >= getSize(list)) ERROR("Index out of bounds List.");	
	return index;
}


static Node* getStartNode(void* list)
{
	CHECK(list);
	return (Node*)((List*)list)->start;
}