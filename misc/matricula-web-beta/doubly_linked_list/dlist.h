#ifndef DLIST_H_INCLUDED
#define DLIST_H_INCLUDED

#include <stdlib.h>

/*
Pointer to a function: This function is necessary
to allocate a node on the doubly linked list;
*/
typedef void* (*dlist_node_constructor_fn) (void*);
/*
Pointer to a function: This function is necessary
to free the memory allocated to a node;
*/
typedef void (*dlist_node_destructor_fn) (void*); 

typedef struct dlist_node_t{
    void* data;
    struct dlist_node_t* next;
    struct dlist_node_t* prev;
}dlist_node_t;

/*Just a node used to iterate over the doubly linked list*/
typedef dlist_node_t* dlist_iterator_t;

typedef struct dlist_t{
    dlist_node_t* head;
    dlist_node_t* tail;
    dlist_node_constructor_fn constructor;
    dlist_node_destructor_fn destructor;
    int size;
}dlist_t;

/*
Function to initialize a doubly liked list:
Parameters:
    - Pointer of a pointer to a doubly linked list;
    - Constructor to a node;
    - Destructor to a node.
*/
void dlist_initialize(dlist_t** l, dlist_node_constructor_fn constructor,
                                dlist_node_destructor_fn destructor);

/*
Function to free the memory allocated to a doubly linked list.
It removes the head until the list is empty.
*/
void dlist_delete(dlist_t** l);

/*
Function to insert a node on the doubly linked list.
The program considers that the positions passed on the
parameters are always valid, that's why it doesn't has 
a verifyer to an invalid position.
*/
void dlist_insert(dlist_t* l, void* data, size_t i);

/*
Function to insert a node on the head of the doubly linked list.
*/
void dlist_prepend(dlist_t* l, void* data);

/*
Function to insert a node on the end of the doubly linked list.
*/
void dlist_append(dlist_t* l, void* data);

/*
Function to remove a node from the doubly linked list.
The program considers that the positions passed on the
parameters are always valid, that's why it doesn't has 
a verifyer to an invalid position.
*/
void dlist_remove(dlist_t* l, size_t i);

/*
Function to remove the node located on the beginning
of the doubly linked list.
*/
void dlist_remove_head(dlist_t* l);

/*
Function to remove the node located on the end of the
doubly linked list.
*/
void dlist_remove_tail(dlist_t* l);

/*
Function to access an element of the doubly linked list.
A pointer to the node is returned.
*/
void* dlist_access(dlist_t* l, size_t i);

/*
Function to access the element located on the beginning
of the doubly linked list.
*/
void* dlist_access_head(dlist_t* l);

/*
Function to access the element located on the end 
of the doubly linked list.
*/
void* dlist_access_tail(dlist_t* l);

/*
Function to return the position of an element
given a key.
*/
int dlist_find(dlist_t* l, void* data);

/*
Function to iterate over the doubly linked list
and process the nodes. The function that processes
each node is explained on another header file.
*/
void dlist_show_elements(dlist_t* l);

/*
Function to return the total amount of nodes
on the doubly linked list.
*/
size_t dlist_size(dlist_t* l);

/*
Function to return a false like value or a true like
value to decide whether is empty or not. 
*/
size_t dlist_empty(dlist_t* l);

#endif