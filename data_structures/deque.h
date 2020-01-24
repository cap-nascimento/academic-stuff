#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

#include <stdlib.h>

typedef void* (*constructor_fn)(void*);
typedef void (*destructor_fn)(void*);

typedef struct Node{
	void* data;
	struct Node* next;
	struct Node* prev;
}Node;

typedef Node* deque_iterator;

typedef struct Deque{
	Node* head;
	Node* tail;
	constructor_fn constructor;
	destructor_fn destructor;
	size_t size;
}Deque;

void deque_initialize(Deque** d, constructor_fn constructor, destructor_fn destructor);

void deque_delete(Deque** d);

void push_front(Deque* d, void* data);

void push_back(Deque* d, void* data);

void pop_front(Deque* d);

void pop_back(Deque* d);

void* access_front(Deque* d);

void* access_back(Deque* d);

size_t size(Deque* d);

size_t empty(Deque* d);

#endif
