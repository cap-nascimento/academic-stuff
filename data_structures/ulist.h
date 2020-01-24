#ifndef ULIST_H_INCLUDED
#define ULIST_H_INCLUDED

#include <stdlib.h>

/*Definição das funções de construção de destruição de dados*/
typedef void* (*constructor_fn)(void*);
typedef void (*destructor_fn)(void*);

/*Estrutura do nó, possuindo um ponteiro de ponteiro para void e um tamanho para o array*/
typedef struct Node{
	void** data;
	struct Node* next;
	struct Node* prev;
	size_t size;
}Node;

/*Apelido para o nó iterador*/
typedef Node* ulist_iterator;

/*Estrutura para a lista desenrolada, com as mesmas características de uma lista encadeada simples/dupla
e uma variável para o tamanho máximo desejado dos arrays*/
typedef struct Ulist{
	Node* head;
	Node* tail;
	constructor_fn constructor;
	destructor_fn destructor;
	size_t size;
	size_t d;
}Ulist;

/*Incializa a lista desenrolada*/
void ulist_initialize(Ulist** l,
					  constructor_fn constructor,
                      destructor_fn destructor,
					  size_t d);

					  
/*Libera a lista desenrolada, assim como os nós e os elementos dos nós*/
void ulist_delete(Ulist** l);

/*Insere elementos nos nós da lista desenrolada*/
void ulist_insert(Ulist* l, size_t i, void* data, int i_case);

/*Remove os elementos e é usada na função Ulist_delete*/
void ulist_remove(Ulist* l, size_t i);

/*Acessa os elementos da lista em posições arbitrárias*/
void* ulist_access(Ulist* l, size_t i);

/*Retorna o tamanho atual da lista*/
size_t ulist_size(Ulist* l);

/*Verifica se a lista está vazia*/
size_t ulist_empty(Ulist* l);

#endif
