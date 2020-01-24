#include <stdio.h>
#include <string.h>
#include "bst.h"
#include "queue.h"

void* constructor_int(void* data){
	void* ptr = (int*)malloc(sizeof(int));
	if(ptr == NULL){
		printf("Error (constructor_int - songs.c)\n");
		exit(EXIT_FAILURE);
	}
	memcpy(ptr, data, sizeof(int));
	return ptr;
}

void destructor_int(void* data){
	free(data);
}

int comparator_int(const void* a, const void* b){
	return(*(int*)a - *(int*)b);
}

// void bfs(tree_node* root){
// 	Queue* q;
// 	initialize_queue(&q, constructor_song, destructor_song);
	
// 	//Muito errado isso daqui:
// 	if(root!=NULL){
// 		push(q, root->data);
// 	}
// 	while(!empty(q)){
// 		tree_node* node = root;
// 		info(node->data);
// 		if(node->left != NULL){
// 			push(q, node->left->data);
// 		}else if(node->right != NULL){
// 			push(q, node->right->data);	
// 		}
// 		pop(q);
// 	}
// 	delete_queue(&q);
// }



void menu(){
	printf("1 - bst_insert;\n");
	printf("2 - bst_remove;\n");
	printf("3 - bst_find;\n");
	printf("4 - traverse_in_order;\n");
	printf("5 - traverse_pre_order;\n");
	printf("6 - traverse_post_order;\n");
	printf("7 - bst_size\n");
	printf("0 - exit;\n");
	printf("Choose: ");
}

int main(){

	bst_t* bst;
	bst_initialize(&bst, constructor_int, destructor_int, comparator_int);
	
	int op;
	menu();
	while(scanf("%d", &op) && op!=0){
		int num, yt;
		switch (op)
		{
		case 1:
			scanf("%d", &num);
			bst_insert(bst, &num);
			break;
		case 2:
			printf("Type the number to be deleted: ");
			scanf("%d", &yt);
			bst_remove(bst, &yt);
			break;
		case 3:
			printf("Type a number to search for: ");
			scanf("%d", &num);
			if(bst_find(bst, &num)){
				printf("The number exists on tree!\n");
			}else{
				printf("The number does not exists on tree!\n");			
			}
			break;
		case 4:
			printf("In order traversal:\n");
			traverse_in_order(bst->root);
			printf("\n");
			break;
		case 5:
			printf("Pre order traversal:\n");
			traverse_pre_order(bst->root);
			printf("\n");
			break;
		case 6:
			printf("Post order traversal:\n");
			traverse_post_order(bst->root);
			printf("\n");
			break;
		case 7:
			printf("bst_size of tree: %ld\n", bst_size(bst));
			break;
		default:
			printf("Invalid option!\n");
			break;
		}
		
		menu();
	}
	
	bst_delete(&bst);

	return 0;
}