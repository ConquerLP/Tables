#include "stack.h"

static void* clone(void* object);
static char* toString(void* object);
static _int getHashvalue(void* object);

static void* peek(void* stack);
static void* pop(void* stack);
static void push(void* stack, void* toPush);
static _int search(void* stack, void* toSearch);

Stack* new_Stack(_int stackSize)
{
	if(stackSize <= 0) ERROR("Stack size is 0 or negative.");
	Stack* stack;
	Malloc(stack, Stack, 1);
	stack->object = new_Object();
	stack->stackPtr = 0;
	stack->stackSize = stackSize;
	Malloc(stack->elements, void*, stackSize);
	for(_int i = 0; i < stackSize; ++i){
		stack->elements[i] = NULL;
	}
	stack->object->clone = clone;
	stack->object->toString = toString;
	stack->object->getHashvalue = getHashvalue;
	
	stack->peek = peek;
	stack->pop = pop;
	stack->push = push;
	stack->search = search;
	updateHashValue(stack);
	return stack;
}

static void* clone(void* object)
{
	CHECK(object);
	Stack* clone = new_Stack(((Stack*)object)->stackSize);
}

static char* toString(void* object)
{
	CHECK(object);
	return "Stack";
}

static _int getHashvalue(void* object)
{
	CHECK(object);
	Stack* stack_ptr = object;
	return (_int)stack_ptr->elements;
}

static void* peek(void* stack)
{
	CHECK(stack);
	Stack* stack_ptr = stack;
	return stack_ptr->elements[stack_ptr->stackPtr];
}

static void* pop(void* stack)
{
	CHECK(stack);
	Stack* stack_ptr = stack;
	if(stack_ptr->stackPtr <= 0) return NULL;
	void* poped = peek(stack);
	stack_ptr->elements[stack_ptr->stackPtr] = NULL;
	stack_ptr->stackPtr -= 1;
	return poped;
}

static void push(void* stack, void* toPush)
{
	CHECK(stack);
	CHECK(toPush);
	Stack* stack_ptr = stack;
	stack_ptr->stackPtr += 1;
	if(stack_ptr->stackPtr > stack_ptr->stackSize) ERROR("Stack overflow.");
	stack_ptr->elements[stack_ptr->stackPtr] = toPush;
}

static _int search(void* stack, void* toSearch)
{
	CHECK(stack);
	CHECK(toSearch);
	Stack* stack_ptr = stack;
	for(_int i = stack_ptr->stackPtr; i >= 0 ; --i){
		if(stack_ptr->elements[i] == toSearch) return i;
	}
	return INVALID_INDEX;
}
