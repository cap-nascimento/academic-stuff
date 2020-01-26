#ifndef DLIST_H_INCLUDED
#define DLIST_H_INCLUDED

#include <stdio.h>

typedef void* (*dlist_node_constructor_fn) (void*);
typedef void (*dlist_node_destructor_fn) (void*); 

typedef struct dlist_node_t{
    void* data;
    struct dlist_node_t* next;
    struct dlist_node_t* prev;
}dlist_node_t;

typedef dlist_node_t* dlist_iterator_t;

typedef struct dlist_t{
    dlist_node_t* head;
    dlist_node_t* tail;
    dlist_node_constructor_fn constructor;
    dlist_node_destructor_fn destructor;
    int size;
}dlist_t;

void dlist_initialize(dlist_t** l, dlist_node_constructor_fn constructor,
                                dlist_node_destructor_fn destructor);

void dlist_delete(dlist_t** l);

void dlist_insert(dlist_t* l, void* data, size_t i);

void dlist_prepend(dlist_t* l, void* data);

void dlist_append(dlist_t* l, void* data);

void dlist_remove(dlist_t* l, size_t i);

void dlist_remove_head(dlist_t* l);

void dlist_remove_tail(dlist_t* l);

void* dlist_access(dlist_t* l, size_t i);

void* dlist_access_head(dlist_t* l);

void* dlist_access_tail(dlist_t* l);

size_t dlist_size(dlist_t* l);

size_t dlist_empty(dlist_t* l);

#endif