#include <stdio.h>
#include <time.h>
#include "treap.h"

static treap_node* new_treap_node(void* data, constructor_fn constructor);
static void delete_treap_node(treap_node* node, destructor_fn destructor);
static void treap_delete_helper(treap_t* t, treap_node* node);
static treap_node* treap_insert_helper(treap_t* t, treap_node* root, void* data);
static treap_node* treap_remove_helper(treap_t* t, treap_node* root, void* data);
static int treap_find_helper(treap_t* t, treap_node* root, void* data);
static treap_node* treap_left_rotate(treap_node* root);
static treap_node* treap_right_rotate(treap_node* root);

void treap_initialize(treap_t** t, constructor_fn constructor, destructor_fn destructor, comparator_fn comparator){
	(*t) = (treap_t*)malloc(sizeof(treap_t));
	(*t)->root = NULL;
	(*t)->constructor = constructor;
	(*t)->destructor = destructor;
	(*t)->comparator = comparator;
	(*t)->size = 0;
}

void treap_delete(treap_t** t){
	treap_delete_helper(*t, (*t)->root);
	free(*t);
	*t = NULL;
}

static void treap_delete_helper(treap_t* t, treap_node* node){
	if(node != NULL){
		treap_delete_helper(t, node->left);
		treap_delete_helper(t, node->right);
		delete_treap_node(node, t->destructor);	
	}
}

static void delete_treap_node(treap_node* node, destructor_fn destructor){
	destructor(node->data);
	free(node);
}

void treap_insert(treap_t* t, void* data){
	t->root = treap_insert_helper(t, t->root, data);
}

static treap_node* treap_insert_helper(treap_t* t, treap_node* root, void* data){
	if(root == NULL){
		root = new_treap_node(data, t->constructor);
		t->size++;	
	}else if(t->comparator(data, root->data) < 0){
		root->left = treap_insert_helper(t, root->left, data);
		if(root->left->priority > root->priority){
			root = treap_right_rotate(root);
		}	
	}else{
		root->right = treap_insert_helper(t, root->right, data);
		if(root->right->priority > root->priority){
			root = treap_left_rotate(root);
		}	
	}
	return root;
}

static treap_node* treap_left_rotate(treap_node* root){
	treap_node* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;
	return newRoot;
}

static treap_node* treap_right_rotate(treap_node* root){
	treap_node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	return newRoot;
}

static treap_node* new_treap_node(void* data, constructor_fn constructor){
	
	srand(time(NULL));	
	
	treap_node* new = (treap_node*)malloc(sizeof(treap_node));
	new->data = constructor(data);
	new->left = NULL;
	new->right = NULL;
	new->priority = 1+(rand()%100);
	return new;
}

void treap_remove(treap_t* t, void* data){
	t->root = treap_remove_helper(t, t->root, data);
}

static treap_node* treap_remove_helper(treap_t* t, treap_node* root, void* data){
	if(root == NULL){
		return root;
	}else if(t->comparator(data, root->data) < 0){
		root->left = treap_remove_helper(t, root->left, data);	
	}else if(t->comparator(data, root->data) > 0){
		root->right = treap_remove_helper(t, root->right, data);	
	}else{
		if(root->left == NULL){
			treap_node* tmp = root->right;
			delete_treap_node(root, t->destructor);
			t->size--;
			root = tmp;	
		}else if(root->right == NULL){
			treap_node* tmp = root->left;
			delete_treap_node(root, t->destructor);
			t->size--;
			root = tmp;	
		}else{
			if(root->left->priority < root->right->priority){
				root = treap_left_rotate(root);
				root->left = treap_remove_helper(t, root->left, data);
			}else{
				root = treap_right_rotate(root);
				root->right = treap_remove_helper(t, root->right, data);			
			}
		}
	}
	return root;
}

size_t treap_find(treap_t* t, void* data){
	return treap_find_helper(t, t->root, data);
}

static int treap_find_helper(treap_t* t, treap_node* root, void* data){
	if(root == NULL){
		return 0;
	}
	
	if(t->comparator(data, root->data) < 0){
		return treap_find_helper(t, root->left, data);	
	}else{
		return treap_find_helper(t, root->right, data);	
	}
	
	return 1;
}

size_t treap_size(treap_t* t){
	return t->size;
}