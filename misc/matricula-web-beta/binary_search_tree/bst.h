#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <stdlib.h>
#include "../doubly_linked_list/dlist.h"

/*
Pointer to a function: This function is necessary to
alloc the data of a node on bst.
*/
typedef void* (*constructor_fn)(void*);
/*
Pointer to a function: This function is necessary to
free a node of a bst.
*/
typedef void (*destructor_fn)(void*);
/*
Pointer to a function: This function is necessary to
do the comparisons through the bst. It is used to
insert, remove and search for a node.
*/
typedef int (*comparator_fn)(const void*, const void*);

typedef struct bst_node{
	void* data;
	struct bst_node* left;
	struct bst_node* right;
}bst_node;

typedef struct bst_t{
	bst_node* root;
	constructor_fn constructor;
	destructor_fn destructor;
	comparator_fn comparator;
	size_t size;
}bst_t;

/*
Function to initialize a binary search tree:
Parameters:
	- Pointer of a pointer to a bst;
	- Constructor of the binary search tree elements;
	- Destructor of the binary search tree elements;
*/
void bst_initialize(bst_t** t, constructor_fn constructor, destructor_fn destructor, comparator_fn comparator);

/*
Function to delete and free the memory allocated
to a binary search tree. It just removes the elements
by depth first search and free the memory;
*/
void bst_delete(bst_t** t);

/*
Function to insert a node on the bst:
The function uses the comparator to traverse the tree
until the function reaches a leaf with nothing
allocated;
*/
void bst_insert(bst_t* t, void* data);

/*
Function to remove a node from the bst:
The function uses the comparator to traverse the tree,
but there are three cases to be considered when the
node with the required key is reached:
	1º - The node has no child: the function simply destroys the node;

	2º - The node has only the left child: the function returns the
	     left child as the root of the nested tree and destroys the node;
	
	3º - The node has only the right child: the function returns the
	     right child as the root of the nested tree and destroys the node;
	
	4º - The node has the left and the right child: The new root of the nested
	     tree is the successor of the actual root. This can be made by swapping the
	     root value with the value of the rightmost node ont he left nested tree.
	     The node is destroyed on the first case;
*/
void bst_remove(bst_t* t, void* data);

/*
Function to verify if a node with a given key exists on the bst;
*/
int bst_find(bst_t* t, void* data);

/*
This function is not for general purposes like the previous ones.
Due to the functionality of the program, we needed a function to
traverse a tree after find it on another tree. So, this function
executes a depth first search to find a node that contains another
binary search tree. After it successfully find the required node,
anothre function is used to complete the process. The other function
is explained on another header file.
*/
void bst_access_modify_subject(bst_t* t, bst_node* root, void* data_sub, void* data_stu);

/*
This function does the same as the previous one, but the final
purpose is slightly different.
*/
void bst_access_extract_subject(bst_t* t, bst_node* root, void* data_sub, dlist_t* l);

/*
This function returns a node with a given key;
*/
void* bst_access(bst_t* t, bst_node* root, void* data_sub);

/*
This function executes a depth first search in order.
Every time a node is reached, another function is used
to process the data allocated on that node. The function
is explained on another header file.
*/
void traverse_in_order_student(bst_node* root);

/*
This function executes a depth first search in order.
Every time a node is reached, another function is used
to process the data allocated on that node. The function
is explained on another header file.
*/
void traverse_in_order_subject(bst_node* root);

/*
This function does a depth first search on the binary
search tree, but has no use on the program.
*/
void traverse_post_order(bst_node* root);

/*
Function to return a integer value representing
the total amount of nodes on the binary search tree.
*/
size_t bst_size(bst_t* t);

#endif
