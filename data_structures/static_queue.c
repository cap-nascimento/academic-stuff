#include <stdio.h>
#include <stdlib.h>
#include "static_queue.h"

fila * create(){
	fila *q = (fila*)malloc(sizeof(fila));
	q->inicio = 0;
	q->fim = 0;
	return q;
}

void enqueue(fila * q, int cod){
	if(!full(q)){
		q->v[q->fim].cod = cod;			
		q->fim = (q->fim+1) % (MAX+1);
	}else{
		printf("Fila cheia!\n");
	}
}

void dequeue(fila * q){
	if(!empty(q)){
		q->inicio = (q->inicio+1)%(MAX+1);
	}else{
		printf("Fila vazia!\n");
	}
}

int full(fila * q){
	return (q->fim+1)%(MAX+1) == q->inicio;
}

int empty(fila * q){
	return q->inicio == q->fim;
}

int size(fila * q){
	if(full(q))
		return MAX;
	if(empty(q))
		return 0;
	if(q->inicio <  q->fim){
		return (q->fim - q->inicio);
	}
	return ((MAX+1) - q->inicio) + q->fim;
}

void show_queue(fila * q){
	if(empty(q)){
		printf("Fila vazia!\n");
	}else{	
		int l = q->fim;
		item x = q->v[q->inicio];
		dequeue(q);
		printf("Fila: %d ", x.cod);
		enqueue(q, x.cod);
		while(l != q->inicio){
			x = q->v[q->inicio];
			dequeue(q);
			printf("%d ", x.cod);
			enqueue(q, x.cod);
		}
		printf("\n");
	}
}