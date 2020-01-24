#include <stdio.h>
#include "bst.h"

static bst_node* new_bst_node(void* data, constructor_fn constructor);
static void delete_bst_node(bst_node* node, destructor_fn destructor);
static void bst_delete_helper(bst_t* t, bst_node* root);
static bst_node* bst_insert_helper(bst_t* t, bst_node* root, void* data);
static bst_node* bst_remove_helper(bst_t* t, bst_node* root, void* data);
static bst_node* bst_rightmost(bst_node* root);
static int bst_find_helper(bst_t* t, bst_node* root, void* data);

void bst_initialize(bst_t** t, constructor_fn constructor, destructor_fn destructor, comparator_fn comparator){
	(*t) = (bst_t*)malloc(sizeof(bst_t));
	(*t)->root = NULL;
	(*t)->constructor = constructor;
	(*t)->destructor = destructor;
	(*t)->comparator = comparator;
	(*t)->size = 0;
}
	
void bst_delete(bst_t** t){
	bst_delete_helper((*t), (*t)->root);
	free(*t);
	(*t) = NULL;
}

static void bst_delete_helper(bst_t* t, bst_node* root){
	if(root != NULL){
		bst_delete_helper(t, root->left);
		bst_delete_helper(t, root->right);
		delete_bst_node(root, t->destructor);	
	}
}

static void delete_bst_node(bst_node* node, destructor_fn destructor){
	destructor(node->data);
	free(node);
}

static bst_node* new_bst_node(void* data, constructor_fn constructor){
	bst_node* new = (bst_node*)malloc(sizeof(bst_node));
	new->data = constructor(data);
	new->left = NULL;
	new->right = NULL;
	return new;
}

void bst_insert(bst_t* t, void* data){
	t->root = bst_insert_helper(t, t->root, data);
}

static bst_node* bst_insert_helper(bst_t* t, bst_node* root, void* data){
	if(root == NULL){
		t->size++;
		root = new_bst_node(data, t->constructor);	
	}else if(t->comparator(data, root->data) < 0){
		root->left = bst_insert_helper(t, root->left, data);
	}else{
		root->right = bst_insert_helper(t, root->right, data);
	}
	return root;
}

void bst_remove(bst_t* t, void* data){
	t->root = bst_remove_helper(t, t->root, data);
}

static bst_node* bst_remove_helper(bst_t* t, bst_node* root, void* data){
	if(root == NULL){
		return root;	
	}else if(t->comparator(data, root->data) < 0){
		root->left = bst_remove_helper(t, root->left, data);	
	}else if(t->comparator(data, root->data) > 0){
		root->right = bst_remove_helper(t, root->right, data);	
	}else{
		if(root->left == NULL){
			bst_node* tmp = root->right;
			delete_bst_node(root, t->destructor);
			t->size--;
			return tmp;
		}else if(root->right == NULL){
			bst_node* tmp = root->left;
			delete_bst_node(root, t->destructor);	
			t->size--;
			return tmp;
		}else{
			bst_node* tmp = bst_rightmost(root->left);
			void* swap = root->data;
			root->data = tmp->data;
			tmp->data = swap;
			root->left = bst_remove_helper(t, root->left, tmp->data);
		}
	}
	return root;
}

static bst_node* bst_rightmost(bst_node* root){
	if(root == NULL || root->right == NULL){
		return root;	
	}else{
		return bst_rightmost(root->right);
	}
}

int bst_find(bst_t* t, void* data){
	return bst_find_helper(t, t->root, data);
}

static int bst_find_helper(bst_t* t, bst_node* root, void* data){
	if(root==NULL){
		return 0;	
	}

	if(t->comparator(data, root->data) < 0){
		return bst_find_helper(t, root->left, data);	
	}else if(t->comparator(data, root->data) > 0){
		return bst_find_helper(t, root->right, data);
	}

	return 1;
}

void traverse_pre_order(bst_node* root){
	if(root != NULL){
		printf("%d ", *(int*)root->data);
		traverse_pre_order(root->left);
		traverse_pre_order(root->right);
	}
}

void traverse_in_order(bst_node* root){
	if(root != NULL){
		traverse_in_order(root->left);
		printf("%d ", *(int*)root->data);
		traverse_in_order(root->right);
	}
}

void traverse_post_order(bst_node* root){
	if(root != NULL){
		traverse_post_order(root->left);
		traverse_post_order(root->right);
		printf("%d ", *(int*)root->data);
	}
}

size_t bst_size(bst_t* t){
	return t->size;
}

