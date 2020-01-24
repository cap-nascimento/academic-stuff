#ifndef PQUEUE_H_INCLUDED
#define PQUEUE_H_INCLUDED

#include <stdlib.h>

typedef void* (*constructor_fn)(void*);
typedef void (*destructor_fn)(void*);
typedef int (*compare_fn)(const void*, const void*);

typedef struct PQueue{
	void** data;
	constructor_fn constructor;
	destructor_fn destructor;
	compare_fn comparator;
	size_t size;
	size_t capacity;
}PQueue;

void pqueue_initialize(PQueue** pq, constructor_fn constructor, destructor_fn destructor, compare_fn comparator);

void pqueue_delete(PQueue** pq);

void push(PQueue* pq, void* data);

void pop(PQueue* pq);

void* front(PQueue* pq);

size_t size(PQueue* pq);

size_t empty(PQueue* pq);

#endif
