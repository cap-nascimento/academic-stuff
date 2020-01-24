#include <stdio.h>
#include "tree.h"

static void delete_tree_node(tree_node* node, destructor_fn destructor);
static tree_node* new_tree_node(void* data, constructor_fn constructor);
static void tree_delete_helper(tree_t* t, tree_node* root);
static tree_node* tree_insert_helper(tree_t* t, tree_node* node, void* data);

static void delete_tree_node(tree_node* node, destructor_fn destructor){
	destructor(node->data);
	free(node);
}

static tree_node* new_tree_node(void* data, constructor_fn constructor){
	tree_node* new = (tree_node*)malloc(sizeof(tree_node));
	new->data = constructor(data);
	new->left = NULL;
	new->right = NULL;
}

void tree_initialize(tree_t** t, constructor_fn constructor, destructor_fn destructor){
	(*t) = (tree_t*)malloc(sizeof(tree_t));
	(*t)->root = NULL;
	(*t)->constructor = constructor;
	(*t)->destructor = destructor;
}

void tree_delete(tree_t** t){
	tree_delete_helper(*t, (*t)->root);
	free(*t);
	*t = NULL;
}

static void tree_delete_helper(tree_t* t, tree_node* root){
	if(root!=NULL){
		tree_delete_helper(t, root->left);
		tree_delete_helper(t, root->right);
		delete_tree_node(root, t->destructor);	
	}
}

tree_node* tree_insert(tree_t* t, void* data){
	return new_tree_node(data, t->constructor);
}