#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdlib.h>

typedef void* (*constructor_fn)(void*);
typedef void (*destructor_fn)(void*);

typedef struct tree_node{
	void* data;
	struct tree_node* left;
	struct tree_node* right;
}tree_node;

typedef struct tree_t{
	tree_node* root;
	constructor_fn constructor;
	destructor_fn destructor;
}tree_t;

void tree_initialize(tree_t** t, constructor_fn constructor, destructor_fn destructor);

void tree_delete(tree_t** t);

tree_node* tree_insert(tree_t* t, void* data);

#endif