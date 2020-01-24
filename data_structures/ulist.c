/*
Autor: Anderson Vieira do Nascimento
Arquivo de implementação das funções da lista desenrolada
*/
#include <stdio.h>
#include "ulist.h"

/*Cria nó em caso de estouro do limite de elementos ou em caso de divisão do nó*/
static Node* createNode(Ulist* l);

/*Divide o nó em dois e faz a devida distribuição de elementos*/
static Node* splitNode(Ulist* l, Node* node);

/*Libera o nó após a retirada de todos os dados do array*/
static void deleteNode(Ulist* l, Node* node);

/*Função para localizar posição de inserção no restauro das propriedades de lista desenrolada*/
static int searchIndex(Ulist* l, Node* node);

static Node* createNode(Ulist* l){
	
	/*Alocação do nó*/
	void* ptr = malloc(sizeof(Node));
	if(ptr == NULL){
		printf("Erro de alocação (createNode).\n");
		exit(EXIT_FAILURE);
	}
	
	/*Inicialização do nó assim como em listas duplamente encadeadas*/
	Node *new = ptr;
	new->next = NULL;
	new->prev = NULL;
	new->size = 0;
	
	/*Alocação do array para o recebimento dos dados*/
	new->data = malloc((l->d)*sizeof(void*));
	return new;
}

static void deleteNode(Ulist* l, Node* node){
	size_t i;
	/*Varre o array e libera as posições de memória com o uso da função destruidora*/
	for(i=0;i<node->size;i++){
		l->destructor(node->data[i]);
	}
	
	/*Libera o nó*/
	free(node);
}

static Node* splitNode(Ulist* l, Node* node){
	
	/*Cria dois nós para receber os dados do array*/
	Node* new = createNode(l);
	Node* aux = createNode(l);
	
	/*Distribui a primeira metade dos elementos do nó para o nó aux*/
	size_t i, k=0;
	for(i=0;i<(l->d)/2;i++){
		aux->data[k] = l->constructor(node->data[i]);
		aux->size++;
		k++;
	}
	
	/*Distribui a segunda metade dos elementos do nó para o nó new*/
	k=0;
	for(i=(l->d)/2;i<l->d;i++){
		new->data[k] = l->constructor(node->data[i]);
		new->size++;
		k++;
	}
	
	/*Caso o nó seja o único na lista, a cabeça passa a ser aux e a cauda passa a ser new.
	A função então retorna a cabeça para o nó passado por parâmetro*/
	if(node == l->head && node->next == NULL && node->prev == NULL){
		
		l->head = aux;
		l->head->next = new;
		new->prev = l->head;
		l->tail = new;
		return l->head;
	}
	
	/*Caso não seja o caso acima, une-se os dois nós criados*/
	aux->next = new;
	new->prev = aux;
	
	/*Caso o nó seja a cabeça, é feita uma inserção do nó aux como cabeça da lista e o nó new
	como nó seguinte. A função retorna a cabeça*/
	if(node == l->head && node->next!=NULL){
		
		new->next = l->head->next;
		l->head->next->prev = new;
		l->head = aux;
		return l->head;
	
	/*Caso o nó seja a cauda, é feita uma inserção do nó new como cauda da lista e o nó aux
	como nó anterior. A função retorna o nó anterior à cauda*/
	}else if(node == l->tail && node->prev!=NULL){
		
		aux->prev = l->tail->prev;
		l->tail->prev->next = aux;
		l->tail = new;
		return l->tail->prev;
		
	/*Caso o nó esteja entre a cabeça e a cauda, atribuímos as posições devidas e atualizamos os
	ponteiros, levando em considerção, também, que os nós aux e new já estão ligados*/	
	}else{
		
		Node* prev = node->prev;
		Node* next = node->next;
		aux->prev = prev;
		new->next = next;
		prev->next = aux;
		next->prev = new;
		return aux;
		
	}
}

static int searchIndex(Ulist* l, Node* node){
	ulist_iterator it = l->head;
	
	/*Esse modelo de iteração sobre a lista se repete nas demais funções, no qual
	incrementamos uma variável k enquanto iteramos sobre o array de cada nó. A função
	retorna k*/
	
	size_t k=0, i;
	while(it!=node){
		for(i=0;i<it->size;i++){
			k++;
		}
		it = it->next;
	}
	return k;
}

/*Incialização da lista*/
void ulist_initialize(Ulist** l,
					  constructor_fn constructor,
                      destructor_fn destructor,
					  size_t d)
{
	
	/*Alocação da estrutura*/
	void* ptr = malloc(sizeof(Ulist));
	if(ptr == NULL){
		printf("Erro, malloc. (ulist_initalize).\n");
		exit(EXIT_FAILURE);
	}
	
	/*Inicializa-se da mesma forma que uma lista encadeada*/
	(*l) = ptr;
	(*l)->head = NULL;
	(*l)->tail = NULL;
	(*l)->constructor = constructor;
	(*l)->destructor = destructor;
	(*l)->size = 0;
	
	/*Parâmetro para o limite de dados no array de cada nó*/
	(*l)->d = d;
}

void ulist_delete(Ulist** l){
	
	/*O apagamento dos dados é feito utilizando a função ulist_remove, que não apenas
	libera os dados como também libera os nós em caso de esvaziamento do array*/
	while(!(ulist_empty(*l))){
		ulist_remove(*l, 0);
	}
	
	/*Liberamos a estrutura*/
	free(*l);
	*l = NULL;
}

void ulist_insert(Ulist* l, size_t i, void* data, int i_case){
	
	/*Avalia a posição passada por parâmetro*/
	if(i<0 || i>l->size){
		printf("Posicao invalida!\n");
		return;
	}
	
	/*Caso a lista esteja vazia, criamos o primeiro nó e inserimos o elemento na posição devida,
	que inevitavelmente será a posição 0 do array do nó criado. Atualizamos a cabeça, a cauda e os
	tamanhos*/
	if(l->size==0){
		
		Node* new = createNode(l);
		new->data[i] = l->constructor(data);
		new->size++;
		
		l->tail = new;
		l->head = new;
		l->size++;
	
	/*Caso não seja a situação acima, é iniciado o processo mais complexo*/
	}else{
		
		/*Itera-se sobre a lista até a posição desejada. Para isso, atribuímos o valor 0
		para uma variável que receberá o valor 1 caso a variável k finalmente chegue ao valor
		de i para a i-ésima posição, que será representada de forma definitiva na variável j.
		Nesse modelo de iteração, a variável it receberá o nó no qual está a posição desejada
		para inserção*/
		
		ulist_iterator it = l->head;
		size_t k=0, j=0, br=0;
		
		/*Caso o parâmetro de tamanho máximo da lista seja maior que 1, realiza-se a iteração*/
		if(l->d > 1){
			
			while(it!=NULL){
			
				if(i==0){
				
				j = 0;
				break;
				
				}else{
					
					for(j=0;j<it->size;j++){
						k++;
						if(k==i){
							j++;
							br=1;
							break;
						}
					}
				
					if(!br){
						it = it->next;
					}else{
						break;
					}
				
				}
			}	
		}
		
		/*Essa parte da função é essencial, pois dirá se a inserção no array do nó está sendo feita
		de maneira normal, ou seja, o usuário está apenas inserindo mais um elemento, ou se o elemento
		está sendo inserido devido a uma realocação após a retirada de um elemento de um nó vizinho.
		Para isso, é passado por parâmetro (automaticamente), uma variável i_case, que se for igual a 1,
		trata-se de uma inserção normal, e caso seja 0, trata-se de uma inserção para restauro da propriedade
		de lista desenrolada*/
		
		if((j==l->d || j==it->size) && it->next != NULL){
			
			if(i_case){
				it = it->next;
				j=0;
			}
			
		}
		
		/*No caso do parâmetro de tamanho máximo ser 1, a lista se comporta como uma lista duplamente encadeada*/
		if(l->d == 1){
		
			/*Criação do novo nó*/
			Node* new = createNode(l);
			new->data[0] = l->constructor(data);
			
			/*Inserção na cabeça*/
			if(i == 0){
				
				new->next = l->head;
				l->head->prev = new;
				l->head = new;
				l->head->size++;
			
			/*Inserção na cauda*/
			}else if(i == ulist_size(l)){
				
				l->tail->next = new;
				new->prev = l->tail;
				l->tail = new;
				l->tail->size++;
			
			/*Inserção arbitrária*/
			}else{
				
				for(j=0;j<i-1;j++){
					it = it->next;
				}
				
				new->next = it->next;
				new->prev = it;
				new->next->prev = new;
				it->next = new;
				it->next->size++;
				
			}
			
			l->size++;
		
		/*Uso da função splitNode caso a inserção no array do nó atual viole a propriedade da lista desenrolada*/		
		}else if((it->size+1 > l->d)){
			
				/*Divide o nó e retoma o processo de inserção*/
				it = splitNode(l, it);
				ulist_insert(l, i, data, i_case);
			
		}else{
			
			/*Movemos os elementos após a posição encontrada para frente*/
			for(k=it->size;k>j;k--){
				it->data[k] = it->data[k-1];
			}
			
			/*Inserimos o elemento na posição*/
			it->data[j] = l->constructor(data);
			it->size++;
			l->size++;
			
		}
	}
}

void ulist_remove(Ulist* l, size_t i){
	
	/*Avalia a posição passada por parâmetro*/
	if(i<0 || i>=ulist_size(l)){
		printf("Posicao invalida!\n");
		return;
	}
	
	/*Caso o tamanho da lista seja 1, liberamos tanto o primeiro elemento do nó existente
	como a cabeça e a cauda da lista*/
	if(l->size == 1){
		
		l->destructor(l->head->data[0]);
		l->head->size--;
		l->size--;
		
		Node* node = l->head;
		
		l->head = NULL;
		l->tail = NULL;
		
		deleteNode(l, node);
	
	/*Caso não seja a situação acima, um processo mais complexo é iniciado*/
	}else{
		
		/*Repetimos a iteração feita na função ulist_insert*/
		ulist_iterator it = l->head;
		size_t k=0, j, br=0;
		while(it!=NULL){
			for(j=0;j<it->size;j++){
				if(k == i){
					br = 1;
					break;
				}
				k++;
			}
			if(!br){
				it = it->next;
			}else{
				break;
			}
		}
		
		/*Encontrada a posição, simplesmente liberamos o elemento encontrado*/
		l->destructor(it->data[j]);
		
		/*Aqui é criado um nó que servirá para organizar os elementos*/
		Node* ptr = createNode(l);
		
		/*Inserimos todos os elementos do nó no qual houve a liberação do elemento,
		com exceção da posição do elemento que foi liberado*/
		
		int index=0;
		for(k=0;k<it->size;k++){
			if(k!=j){
				ptr->data[index] = it->data[k];
				index++;
			}
		}
		
		/*O ponteiro com os elementos do nó recebe o ponteiro com os elementos reorganizados*/
		it->data = ptr->data;
		it->size--;
		
		/*Aqui analisamos as propriedades da lista desenrolada. Caso o nó possua menos que d/2
		elementos, o nó seguinte (ou anterior) existe e ainda não saia da propriedade de lista desenrolada caso
		um elemento seja retirado do array, passamos o primeiro elemento (ou o último) para o array do qual
		acabamos de retirar*/
		
		if(it->size < (l->d)/2 && it->size > 0){
			
			/*Retira-se o primeiro elemento do array do nó seguinte caso ele obedeça às condições acima*/
			if((it->next!=NULL) && ((it->next->size-1) >= (l->d)/2)){
				
				it->data[it->size] = it->next->data[0];
				it->size++;
				
				k=0;
				Node* ptr2 = createNode(l);
				index=0;
				for(k=1;k<it->next->size;k++){
					ptr2->data[index] = it->next->data[k];
					index++;
				}
				it->next->data = ptr2->data;
				it->next->size--;
				
			/*Retira-se o último elemento do array anterior caso ele obedeça às condições acima*/	
			}else if((it->prev!=NULL) && ((it->prev->size-1) >= (l->d)/2)){
				
				it->data[it->size] = it->data[it->size-1];
				it->data[it->size-1] = it->prev->data[it->prev->size-1];
				it->size++;
				
				k=0;
				Node* ptr2 = createNode(l);
				index=0;
				for(k=0;k<it->prev->size-1;k++){
					ptr2->data[index] = it->prev->data[k];
					index++;
				}
				it->prev->data = ptr2->data;
				it->prev->size--;
			
			/*Caso seja impossível fazer essa realocação de elementos, unimos os elementos do array
			atual com os elementos do array seguinte*/
			}else{
				k=0;
				
				/*Se o nó for a cauda, não tem sentido ir ao próximo nó para transferir os elementos dele,
				pois não existe (NULL)*/
				if(it!=l->tail){
					it = it->next;
				}
				
				/*Caso o nó seja a cabeça, a função searchIndex apresentará erro quando for buscar a posição
				para a inserção dos elementos, pois a busca é feita em uma iteração do começo da lista até o nó
				no qual desejamos fazer a retirada dos elementos para junção*/
				if(it!=l->head){
					
					/*Enquanto o array do nó não estiver vazio, retiramos os elementos um a um e inserimos no array
					superior usando searchIndex e ulist_insert*/
					while(it->size>0){
						void* data = it->data[k];
						index = searchIndex(l, it);
						ulist_insert(l, index, data, 0);
						l->destructor(it->data[k]);
						it->size--;
						l->size--;
						k++;
					}
				}
			}
		}
		
		/*Faz as devidas liberações e atualização de ponteiros quando os nós forem
		esvaziados. Lembrando que na junção, sempre haverá liberação de nó, por isso
		it = it->next na linha 382*/
		if(it->size == 0){
			Node* node = it;
			if(it == l->head){
				l->head = l->head->next;
				l->head->prev = NULL;
				deleteNode(l, node);
			}else if(it == l->tail){
				l->tail = l->tail->prev;
				l->tail->next = NULL;
				deleteNode(l, node);
			}else{
				it->prev->next = it->next;
				it->next->prev = it->prev;
				deleteNode(l, node);
			}
		}
		l->size--;
	}
}

void* ulist_access(Ulist* l, size_t i){
	
	/*Avalia a posição passada por parâmetro*/
	if(i<0 || i>=ulist_size(l)){
		printf("Posicao invalida!\n");
		return NULL;
	}
	
	/*Se for a primeira, retorna o primeiro elemento da cabeça*/
	if(i==0){
		
		return l->head->data[i];
		
	/*Se for a última, retorna o último elemento da cauda (acesso em O(1))*/	
	}else if(i==l->size-1){
		
		return l->tail->data[l->tail->size-1];
		
	/*Caso esteja entre a primeira e a última, segue o modelo de iteração usado até o momento*/	
	}else{
		
		ulist_iterator it = l->head;
		size_t k=0, j, br=0;
		while(it!=NULL){
			for(j=0;j<it->size;j++){
				if(k==i){
					br = 1;
					break;
				}
				k++;
			}
			if(!br){
				it = it->next;
			}else{
				break;
			}
		}
		
		return(it->data[j]);
		
	}
}

size_t ulist_size(Ulist* l){
	/*Retorna o tamanho da lista*/
	return(l->size);
}

size_t ulist_empty(Ulist* l){
	/*Diz se está vazia ou não*/
	return(ulist_size(l) == 0 ? 1 : 0);
}