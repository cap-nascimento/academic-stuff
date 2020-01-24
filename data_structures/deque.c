#include <stdio.h>
#include "deque.h"

static Node* newNode(void* data, constructor_fn constructor);
static void deleteNode(Node* node, destructor_fn destructor);

static Node* newNode(void* data, constructor_fn constructor){
	void* ptr = (Node*)malloc(sizeof(Node));
	if(ptr == NULL){
		printf("Erro, malloc (newNode)\n");
		exit(EXIT_FAILURE);
	}
	Node* new = ptr;
	new->data = constructor(data);
	new->next = NULL;
	new->prev = NULL;
	return new;
}

static void deleteNode(Node* node, destructor_fn destructor){
	destructor(node->data);
	free(node);
}

void deque_initialize(Deque** d, constructor_fn constructor, destructor_fn destructor){
	void* ptr = (Deque*)malloc(sizeof(Deque));
	if(ptr == NULL){
		printf("Erro, malloc (deque_initialize)\n");
		exit(EXIT_FAILURE);
	}
	(*d) = ptr;
	(*d)->head = NULL;
	(*d)->tail = NULL;
	(*d)->constructor = constructor;
	(*d)->destructor = destructor;
	(*d)->size = 0;
}

void deque_delete(Deque** d){
	while(!(empty(*d))){
		pop_front(*d);
	}
	free(*d);
	*d = NULL;
}

void push_front(Deque* d, void* data){
	Node* new = newNode(data, d->constructor);
	if(empty(d)){
		d->tail = new;
	}else{
		d->head->prev = new;
	}
	new->next = d->head;
	d->head = new;
	d->size++;
}

void push_back(Deque* d, void*  data){
	Node* new = newNode(data, d->constructor);
	if(empty(d)){
		d->head = new;
	}else{
		d->tail->next = new;
	}
	new->prev = d->tail;
	d->tail = new;
	d->size++;
}

void pop_front(Deque* d){
	Node* node = d->head;
	if(size(d)==1){
		d->head = NULL;
		d->tail = NULL;
	}else{
		d->head = d->head->next;
		d->head->prev = NULL;
	}
	deleteNode(node, d->destructor);
	d->size--;
}

void pop_back(Deque* d){
	Node* node = d->tail;
	if(size(d)==1){
		d->head = NULL;
		d->tail = NULL;
	}else{
		d->tail = d->tail->prev;
		d->tail->next = NULL;
	}
	deleteNode(node, d->destructor);
	d->size--;
}

void* access_front(Deque* d){
	return(d->head->data);
}

void* access_back(Deque* d){
	return(d->tail->data);
}

size_t size(Deque* d){
	return(d->size);
}

size_t empty(Deque* d){
	return(size(d)==0 ? 1 : 0);
}
