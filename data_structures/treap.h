#ifndef TREAP_H_INCLUDED
#define TREAP_H_INCLUDED

#include <stdlib.h>

typedef void* (*constructor_fn)(void*);
typedef void (*destructor_fn)(void*);
typedef int (*comparator_fn)(const void*, const void*);

typedef struct treap_node{
	void* data;
	struct treap_node* left;
	struct treap_node* right;
	size_t priority;
}treap_node;

typedef struct treap_t{
	treap_node* root;
	constructor_fn constructor;
	destructor_fn destructor;
	comparator_fn comparator;
	size_t size;	
}treap_t;

void treap_initialize(treap_t** t, constructor_fn constructor, destructor_fn destructor, comparator_fn comparator);

void treap_delete(treap_t** t);

void treap_insert(treap_t* t, void* data);

void treap_remove(treap_t* t, void* data);

size_t treap_find(treap_t* t, void* data);

size_t treap_size(treap_t* t);

#endif