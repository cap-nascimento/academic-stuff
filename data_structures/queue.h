#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdlib.h>

typedef void* (*constructor_fn)(void*);
typedef void (*destructor_fn)(void*);

typedef struct queue_node{
	void* data;
	struct queue_node* next;
}queue_node;

typedef struct queue_t{	
	queue_node* front;
	queue_node* back;
	constructor_fn constructor;
	destructor_fn destructor;
	size_t size;
}queue_t;

void queue_initialize(queue_t** q, constructor_fn constructor, destructor_fn destructor);

void queue_delete(queue_t** q);

void queue_push(queue_t* q, void* data);

void queue_pop(queue_t* q);

void* queue_front(queue_t* q);

size_t queue_size(queue_t* q);

size_t queue_empty(queue_t* q);

#endif
