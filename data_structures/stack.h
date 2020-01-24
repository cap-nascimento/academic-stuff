#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdlib.h>

typedef void* (*constructor_fn)(void*);
typedef void (*destructor_fn)(void*);

typedef struct stack_node{
	void* data;
	struct stack_node* next;
}stack_node;

typedef struct stack_t{
	stack_node* top;
	constructor_fn constructor;
	destructor_fn destructor;
	size_t size;
}stack_t;

void stack_initialize(stack_t** s, constructor_fn constructor, destructor_fn destructor);

void stack_delete(stack_t** s);

void stack_push(stack_t* s, void* data);

void stack_pop(stack_t* s);

void* stack_top(stack_t* s);

size_t stack_size(stack_t* s);

size_t stack_empty(stack_t* s);

#endif