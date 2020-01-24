#include <stdio.h>
#include "pqueue.h"

static void pqueue_heapify_bottom(PQueue* pq, size_t i){
	size_t p;
	for(p=(i-1);i!=0;p=(p-1)/2){
		if(pq->comparator(pq->data[i], pq->data[p])<=0){
			break;
		}
		void* aux = pq->data[i];
		pq->data[i] = pq->data[p];
		pq->data[p] = aux;
		i = p;
	}
}

static void pqueue_heapify_top(PQueue* pq, size_t i){
	size_t l, r;
	size_t largest = i;
	while(i<size(pq)){
		i = largest;
		l = 2*i+1;
		r = 2*i+2;
		if(l<size(pq) && pq->comparator(pq->data[i], pq->data[l])<=0){
			largest = l;
		}
		if(r<size(pq) && pq->comparator(pq->data[largest], pq->data[r])<0){
			largest = r;
		}
		if(largest == i){
			break;
		}
		void* aux = pq->data[i];
		pq->data[i] = pq->data[largest];
		pq->data[largest] = aux;
	}
}

void pqueue_initialize(PQueue** pq, constructor_fn constructor, destructor_fn destructor, compare_fn comparator){
	void* ptr = (PQueue*)malloc(sizeof(PQueue));
	if(ptr == NULL){
		printf("Erro, malloc! (pqueue_initialize)\n");
		exit(EXIT_FAILURE);
	}
	(*pq) = ptr;
	(*pq)->data = NULL;
	(*pq)->constructor = constructor;
	(*pq)->destructor = destructor;
	(*pq)->comparator = comparator;
	(*pq)->size = 0;
	(*pq)->capacity = 0;
}

void pqueue_delete(PQueue** pq){
	while(!(empty(*pq))){
		pop(*pq);
	}
	free(*pq);
	*pq = NULL;
}

void push(PQueue* pq, void* data){
	if(pq->size == pq->capacity){
		if(pq->capacity == 0){
			pq->capacity = 1;
		}else{
			pq->capacity *= 2; 
		}
		
		void* ptr = (void*)realloc(pq->data, pq->capacity*sizeof(void*));
		if(ptr == NULL && (pq->capacity*sizeof(void*))!=0){
			printf("Erro, realloc! (push)\n");
			exit(EXIT_FAILURE);
		}
		pq->data = ptr;
	}
	pq->data[pq->size] = pq->constructor(data);
	pqueue_heapify_bottom(pq, pq->size);
	pq->size++;
}

void pop(PQueue* pq){
	pq->size--;
	pq->destructor(pq->data[0]);
	if(!(empty(pq))){
		pq->data[0] = pq->data[pq->size];
		pqueue_heapify_top(pq, 0);
	}
	if(pq->size == pq->capacity/2){
		void* ptr = (void*)realloc(pq->data, (pq->capacity/2)*sizeof(void*));
		if(ptr == NULL && ((pq->capacity/2)*sizeof(void*))!=0){
			printf("Erro, realloc! (pop)\n");
			exit(EXIT_FAILURE);
		}
		pq->data = ptr;
		pq->capacity = pq->capacity/2;
	}
}

void* front(PQueue* pq){
	return(pq->data[0]);
}

size_t size(PQueue* pq){
	return pq->size;
}

size_t empty(PQueue* pq){
	return(size(pq) == 0 ? 1 : 0);
}
