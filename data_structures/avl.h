#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include <stdlib.h>

typedef void* (*constructor_fn)(void*);
typedef void (*destructor_fn)(void*);
typedef int (*comparator_fn)(const void*, const void*);

typedef struct avl_node{
	void* data;
	size_t height;
	struct avl_node* left;
	struct avl_node* right;
}avl_node;

typedef struct avl_t{
	avl_node* root;
	constructor_fn constructor;
	destructor_fn destructor;
	comparator_fn comparator;
	size_t size;
}avl_t;

void avl_initialize(avl_t** t, constructor_fn constructor, destructor_fn destructor, comparator_fn comparator);

void avl_delete(avl_t** t);

void avl_insert(avl_t* t, void* data);

void avl_remove(avl_t* t, void* data);

int avl_find(avl_t* t, void* data);

size_t avl_size(avl_t* a);

#endif
