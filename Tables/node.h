#ifndef NODE_H

#define NODE_H

#include "macros.h"

typedef struct _Node{
	void* content;
	struct _Node* next;
	struct _Node* prev;
}Node;

Node* new_Node(void* content);
void* node_get(Node* node);
Node* node_get_N(Node* node, _int index);
void node_insert_before(Node* node, Node* insterted);
void node_insert_after(Node* node, Node* insterted);
void node_replace_N(Node* node, void* content, _int index);
void node_pop(Node* node, _int index);

#endif