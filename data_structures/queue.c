#include <stdio.h>
#include "queue.h"

static queue_node* new_queue_node(void* data, constructor_fn constructor);
static void delete_queue_node(queue_node* node, destructor_fn destructor);

void queue_initialize(queue_t** q, constructor_fn constructor, destructor_fn destructor){
	(*q) = (queue_t*)malloc(sizeof(queue_t));
	(*q)->front = NULL;
	(*q)->back = NULL;
	(*q)->constructor = constructor;
	(*q)->destructor = destructor;
	(*q)->size = 0;
}

static void delete_queue_node(queue_node* node, destructor_fn destructor){
	destructor(node->data);
	free(node);
}

void queue_delete(queue_t** q){
	while(!queue_empty(*q)){
		queue_pop(*q);
	}
	free(*q);
	*q = NULL;
}

void queue_push(queue_t* q, void* data){
	queue_node* new = new_queue_node(data, q->constructor);
	if(queue_empty(q)){
		q->front = new;
	}else{
		q->back->next = new;
	}
	q->back = new;
	q->size++;
}

static queue_node* new_queue_node(void* data, constructor_fn constructor){
	queue_node* new = (queue_node*)malloc(sizeof(queue_node));
	new->data = constructor(data);
	new->next = NULL;
	return new;
}

void queue_pop(queue_t* q){
	queue_node* node = q->front;
	if(queue_size(q) == 1){
		q->front = NULL;
		q->back = NULL;	
	}else{
		q->front = node->next;
	}
	delete_queue_node(node, q->destructor);
	q->size--;
	
}

void* queue_front(queue_t* q){
	return q->front->data;
}

size_t queue_size(queue_t* q){
	return q->size;
}

size_t queue_empty(queue_t* q){
	return(q->size == 0 ? 1 : 0);
}

