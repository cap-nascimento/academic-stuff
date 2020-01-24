#include <stdio.h>
#include "stack.h"

static stack_node* new_stack_node(void* data, constructor_fn constructor);
static void delete_stack_node(stack_node* node, destructor_fn destructor);

static stack_node* new_stack_node(void* data, constructor_fn constructor){
	stack_node* new = (stack_node*)malloc(sizeof(stack_node));
	new->data = constructor(data);
	new->next = NULL;
	return new;
}

static void delete_stack_node(stack_node* node, destructor_fn destructor){
	destructor(node->data);
	free(node);
}

void stack_initialize(stack_t** s, constructor_fn constructor, destructor_fn destructor){
	(*s) = (stack_t*)malloc(sizeof(stack_t));
	(*s)->top = NULL;
	(*s)->constructor = constructor;
	(*s)->destructor = destructor;
	(*s)->size = 0;
}

void stack_delete(stack_t** s){
	while(!stack_empty(*s)){
		stack_pop(*s);	
	}
	free(*s);
	*s = NULL;
}

void stack_push(stack_t* s, void* data){
	stack_node* new = new_stack_node(data, s->constructor);
	new->next = s->top;
	//if(stack_empty(s)){}
	s->top = new;
	s->size++;
}

void stack_pop(stack_t* s){
	stack_node* node = s->top;
	if(stack_size(s) == 1){
		s->top = NULL;	
	}else{
		s->top = node->next;
	}
	delete_stack_node(node, s->destructor);
	s->size--;
}

void* stack_top(stack_t* s){
	return(s->top->data);
}

size_t stack_size(stack_t* s){
	return(s->size);
}

size_t stack_empty(stack_t* s){
	return(stack_size(s)==0 ? 1 : 0);
}