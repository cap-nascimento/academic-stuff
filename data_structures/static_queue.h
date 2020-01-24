#ifndef STATIC_QUEUE_H_INCLUDED
#define STATIC_QUEUE_H_INCLUDED
#define MAX 20

typedef struct item{
	int cod;
}item;

typedef struct fila{
	int inicio, fim;
	item v[MAX+1];
}fila;

fila * create();
void enqueue(fila * q, int cod);
void dequeue(fila * q);
int full(fila * q);
int empty(fila * q);
int size(fila * q);
void show_queue(fila * q);


#endif