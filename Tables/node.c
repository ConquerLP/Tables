#include "node.h"

Node* new_Node(void* content)
{
	CHECK(content);
	Node* node;
	Malloc(node, Node, 1);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void* node_get(Node* node)
{
	CHECK(node);
	return node->content;
}

Node* node_get_N(Node* node, _int index)
{
	CHECK(node);
	if(index < 0) return NULL;
	if(index == 0) return node;
	Node* temp = node;
	_int i = 0;
	while(temp != NULL){
		temp = temp->next;
		i++;
		if(i == index) break;
	}
	if(i != index || temp == NULL) ERROR("Index out of bounds Nodes.");
	return tmp;
}

void node_insert_before(Node* node, Node* insterted)
{
	CHECK(node);
	CHECK(inserted);
	if(node->prev){
		inserted->prev = node->prev;
		node->prev->next = inserted;
		inserted->next = node;
		node->prev = inserted;
	}
	else {
		inserted->prev = NULL;
		inserted->next = node;
		node->prev = inserted;
	}
}

void node_insert_after(Node* node, Node* insterted)
{
	CHECK(node);
	CHECK(inserted);
	if(node->next){
		node->next->prev = inserted;
		inserted->next = node->next;
		inserted->prev = node;
		node->next = inserted;
	}
	else {
		inserted->next = NULL;
		inserted->prev = node;
		node->next = inserted;
	}
}

void node_replace_N(Node* node, void* content, _int index)
{
	Node* get = node_get_N(node, index);
	get->content = content;
}

void node_pop(Node* node, _int index)
{
	CHECK(node);
	Node* get = node_get_N(node, index);
	if(node->next && node->prev){
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	else if(node->next){
		node->next->prev = NULL;
	}
	else {
		node->prev->next = NULL;
	}
}

