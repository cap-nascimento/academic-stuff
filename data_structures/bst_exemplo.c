#include <stdio.h>
#include <string.h>
#include "bst.h"
//#include "queue.h"

typedef struct Song{
	char title[100];
	char artist[100];
	int length;
	int youtube_access;
}Song;

void* constructor_song(void* data){
	void* ptr = (Song*)malloc(sizeof(Song));
	if(ptr == NULL){
		printf("Erro de alocacao! (constructor_song).\n");
		exit(EXIT_FAILURE);
	}
	memcpy(ptr, data, sizeof(Song));
	return ptr;	
}

void destructor_song(void* data){
	free(data);
}

int comparator_song(const void* a, const void* b){

	Song A = *(Song*)a;
	Song B = *(Song*)b;
	
	int ya1 = A.youtube_access;
	int ya2 = B.youtube_access;
	
	if(ya1 < ya2){
		return -1;
	}else if(ya1 > ya2){
		return 1;
	}
	return 0;
}

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

void info(Song* s){
	printf("\n********** Song Info **********\n");
	printf("Title: %s\n", s->title);
	printf("Artist: %s\n", s->artist);
	printf("Duration: %d\n", s->length);
	printf("Youtube views: %d\n", s->youtube_access);
	printf("*******************************\n\n");
}

/*void bfs(tree_node* root){
	Queue* q;
	initialize_queue(&q, constructor_song, destructor_song);
	
	//Muito errado isso daqui:
	if(root!=NULL){
		push(q, root->data);
	}
	while(!empty(q)){
		tree_node* node = root;
		info(node->data);
		if(node->left != NULL){
			push(q, node->left->data);
		}else if(node->right != NULL){
			push(q, node->right->data);	
		}
		pop(q);
	}
	delete_queue(&q);
}*/

void menu(){
	printf("1 - Inserir;\n2 - remover;\n3 - Buscar;\n4 - Ver tamanho;\n0 - Sair;\nEscolha: ");
}

void inputInfo(Song* s){
	printf("Digite o nome da musica: ");
	scanf("\n%99[^\n]%*c", s->title);
	printf("Digite o artista da musica: ");
	scanf("\n%99[^\n]%*c", s->artist);
	printf("Duracao da musica (em segundos): ");
	scanf("%d", &s->length);
	printf("Acessos no YouTube: ");
	scanf("%d", &s->youtube_access);
	printf("\n");
}

int main(){

	binarySearchTree* bst;
	//inicializar(&bst, constructor_song, destructor_song, comparator_song);
	inicializar(&bst, constructor_int, destructor_int, comparator_int);
	
	//bfs(bst->root);
	
	int op;
	menu();
	while(scanf("%d", &op) && op!=0){
		if(op == 1){
			//Song s;
			//inputInfo(&s);
			//inserir(bst, &s);
			int num;
			scanf("%d", &num);
			inserir(bst, &num);
		}else if(op == 2){
			printf("Digite o numero a ser deletado: ");
			int yt;
			scanf("%d", &yt);
			remover(bst, &yt);		
		}else if(op == 3){
			printf("Digite o numero a ser buscado: ");
			int num;
			scanf("%d", &num);
			if(buscar(bst, &num)){
				printf("Numero encontrado!\n");
			}else{
				printf("Numero nao encontrado!\n");			
			}
		}else if(op == 4){
			printf("Tamanho da arvore: %d\n", tamanho(bst));
		}
		
		menu();
	}
	
	deletar(&bst);

	return 0;
}