#include <stdio.h>
#include "avl.h"

static avl_node* new_avl_node(void* data, constructor_fn constructor);
static void delete_avl_node(avl_node* node, destructor_fn destructor);
static void avl_delete_helper(avl_t* t, avl_node* root);
static avl_node* avl_insert_helper(avl_t* t, avl_node* root, void* data);
static avl_node* avl_remove_helper(avl_t* t, avl_node* root, void* data);
static int avl_find_helper(avl_t* t, avl_node* root, void* data);
static size_t get_node_height(avl_node* root);
static size_t calculate_node_height(avl_node* root);
static int get_node_balance(avl_node* root);
static avl_node* avl_rightmost(avl_node* root);
static avl_node* avl_left_rotate(avl_node* x);
static avl_node* avl_right_rotate(avl_node* y);

void avl_initialize(avl_t** t, constructor_fn constructor, destructor_fn destructor, comparator_fn comparator){
	(*t) = (avl_t*)malloc(sizeof(avl_t));
	(*t)->root = NULL;
	(*t)->constructor = constructor;
	(*t)->destructor = destructor;
	(*t)->comparator = comparator;
	(*t)->size=0;
}

void avl_delete(avl_t** t){
	avl_delete_helper(*t, (*t)->root);
	free(*t);
	*t = NULL;
}

static void avl_delete_helper(avl_t* t, avl_node* root){
	if(root!=NULL){
		avl_delete_helper(t, root->left);
		avl_delete_helper(t, root->right);
		delete_avl_node(root, t->destructor);
	}
}

static void delete_avl_node(avl_node* node, destructor_fn destructor){
	destructor(node->data);
	free(node);
}

static size_t get_node_height(avl_node* root){
	if(root == NULL){
		return 0;	
	}
	return root->height;
}

static size_t calculate_node_height(avl_node* root){
	size_t heightLeft, heightRight;
	if(root == NULL){
		return 0;	
	}
	heightLeft = get_node_height(root->left);
	heightRight = get_node_height(root->right);

	if(heightLeft > heightRight){
		return heightLeft+1;
	}
	return heightRight+1;
}

static int get_node_balance(avl_node* root){
	if(root == NULL){
		return 0;	
	}
	return ((int)get_node_height(root->left) - get_node_height(root->right));
}

static avl_node* avl_rightmost(avl_node* root){
	if(root == NULL || root->right == NULL){
		return root;	
	}else{
		return avl_rightmost(root->right);
	}
}

static avl_node* avl_left_rotate(avl_node* root){
	avl_node* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;
	root->height = calculate_node_height(root);
	newRoot->height = calculate_node_height(newRoot);
	return newRoot;
}

static avl_node* avl_right_rotate(avl_node* root){
	avl_node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	root->height = calculate_node_height(root);
	newRoot->height = calculate_node_height(newRoot);
	return newRoot;
}

void avl_insert(avl_t* t, void* data){
	t->root = avl_insert_helper(t, t->root, data);
}

/*static avl_node* avl_left_rotate(avl_node* x){
    //assert(x!=NULL);
    avl_node* y = x->right;
    //assert(y!=NULL);
    x->right = y->left;
    y->left = x;
    x->height = calculate_node_height(x);
    y->height = calculate_node_height(y);
    return y;
}*/

/* Performa uma rotação para direita.

        y                              x
       / \     Right Rotation         / \
      x   T3   – – – – – – – >       T1  y
     / \                                / \
    T1 T2                              T2 T3
*/

/*static avl_node* avl_right_rotate(avl_node* y){
    //assert(y!=NULL);
    avl_node* x = y->left;
    //assert(x!=NULL);
    y->left = x->right;
    x->right = y;
    y->height = calculate_node_height(y);
    x->height = calculate_node_height(x);
    return x;
}*/

static avl_node* avl_insert_helper(avl_t* t, avl_node* root, void* data){
	if(root == NULL){
		t->size++;
		root = new_avl_node(data, t->constructor);	
	}else if(t->comparator(data, root->data) < 0){
		root->left = avl_insert_helper(t, root->left, data);	
	}else{
		root->right = avl_insert_helper(t, root->right, data);
	}

	root->height = calculate_node_height(root);
	int balance = get_node_balance(root);

	if(balance > 1 && get_node_balance(root->left) >= 0){
		return avl_right_rotate(root);	
	}

	if(balance < -1 && get_node_balance(root->right) <= 0){
		return avl_left_rotate(root);
	}

	if(balance > 1 && get_node_balance(root->left) < 0){
		root->left = avl_left_rotate(root->left);
		return avl_right_rotate(root);
	}

	if(balance < -1 && get_node_balance(root->right) > 0){
		root->right = avl_right_rotate(root->right);
		return avl_left_rotate(root);
	}
	return root;
}

static avl_node* new_avl_node(void* data, constructor_fn constructor){
	avl_node* new = (avl_node*)malloc(sizeof(avl_node));
	new->data = constructor(data);
	new->left = NULL;
	new->right = NULL;
	new->height = 1;
	return new;
}

void avl_remove(avl_t* t, void* data){
	t->root = avl_remove_helper(t, t->root, data);
}

static avl_node* avl_remove_helper(avl_t* t, avl_node* root, void* data){
	if(root == NULL){
		return root;
	}else if(t->comparator(data, root->data) < 0){
		root->left = avl_remove_helper(t, root->left, data);
	}else if(t->comparator(data, root->data) > 0){
		root->right = avl_remove_helper(t, root->right, data);
	}else{
		if(root->left == NULL){
			avl_node* tmp = root->right;
			delete_avl_node(root, t->destructor);
			t->size--;
			return tmp;	
		}else if(root->right == NULL){
			avl_node* tmp = root->left;
			delete_avl_node(root, t->destructor);
			t->size--;
			return tmp;	
		}else{
			avl_node* tmp = avl_rightmost(root->left);
			void* swap = root->data;
			root->data = tmp->data;
			tmp->data = swap;
			root->left = avl_remove_helper(t, root->left, tmp->data);
		}
	}

	if(root == NULL){
		return NULL;	
	}
	root->height = calculate_node_height(root);
	int balance = get_node_balance(root);

	if(balance > 1 && get_node_balance(root->left) >= 0){
		return avl_right_rotate(root);
	}

	if(balance < -1 && get_node_balance(root->right) <= 0){
		return avl_left_rotate(root);
	}

	if(balance > 1 && get_node_balance(root->left) < 0){
		root->left = avl_left_rotate(root->left);
		return avl_right_rotate(root);	
	}

	if(balance < -1 && get_node_balance(root->right) > 0){
		root->right = avl_right_rotate(root->right);
		return avl_left_rotate(root);	
	}
	return root;
}

int avl_find(avl_t* t, void* data){
	return avl_find_helper(t, t->root, data);
}

static int avl_find_helper(avl_t* t, avl_node* root, void* data){
	if(root == NULL){
		return 0;	
	}

	if(t->comparator(data, root->data) < 0){
		return avl_find_helper(t, root->left, data);	
	}else{
		return avl_find_helper(t, root->right, data);
	}

	return 1;
}

size_t avl_size(avl_t* t){
	return t->size;
}

