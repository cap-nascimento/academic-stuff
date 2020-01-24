#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <stdlib.h>

typedef void* (*constructor_fn)(void*);
typedef void (*destructor_fn)(void*);
typedef int (*comparator_fn)(const void*, const void*);

typedef struct bst_node{
	void* data;
	struct bst_node* left;
	struct bst_node* right;
}bst_node;

typedef struct bst_t{
	bst_node* root;
	constructor_fn constructor;
	destructor_fn destructor;
	comparator_fn comparator;
	size_t size;
}bst_t;

void bst_initialize(bst_t** t, constructor_fn constructor, destructor_fn destructor, comparator_fn comparator);

void bst_delete(bst_t** t);

void bst_insert(bst_t* t, void* data);

void bst_remove(bst_t* t, void* data);

int bst_find(bst_t* t, void* data);

size_t bst_size(bst_t* t);

#endif
