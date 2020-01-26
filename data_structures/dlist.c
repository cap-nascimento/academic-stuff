#include <stdlib.h>
#include "dlist.h"

static dlist_node_t* dlist_new_node(void* data, dlist_node_constructor_fn constructor);

static void dlist_delete_node(dlist_node_t* n, dlist_node_destructor_fn destructor);

static dlist_node_t* dlist_new_node(void* data, dlist_node_constructor_fn constructor){
    dlist_node_t* new_node = (dlist_node_t*)malloc(sizeof(dlist_node_t));
    new_node->data = constructor(data);
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

static void dlist_delete_node(dlist_node_t* n, dlist_node_destructor_fn destructor){
    destructor(n->data);
    free(n);
}

void dlist_initialize(dlist_t** l, dlist_node_constructor_fn constructor,
dlist_node_destructor_fn destructor){
    (*l) = (dlist_t*)malloc(sizeof(dlist_t));
    (*l)->head = NULL;
    (*l)->tail = NULL;
    (*l)->size = 0;
    (*l)->constructor = constructor;
    (*l)->destructor = destructor;
}

void dlist_delete(dlist_t** l){
    while(!dlist_empty(*l)){
        dlist_remove_head(*l);
    }
    free(*l);
    *l = NULL;
}

void dlist_insert(dlist_t* l, void* data, size_t i){
    if(dlist_empty(l) || i == 0){
        dlist_prepend(l, data);
    }else if(i == dlist_size(l)){
        dlist_append(l, data);
    }else{
        dlist_node_t* new_node = dlist_new_node(data, l->constructor);
        dlist_iterator_t it = l->head;
        size_t k;
        for(k=0;k<i-1;k++){
            it = it->next;
        }
        new_node->next = it->next;
        new_node->prev = it;
        it->next = new_node;
        it->next->prev = new_node;
        l->size++;
    }
}

void dlist_prepend(dlist_t* l, void* data){
    dlist_node_t* new_node = dlist_new_node(data, l->constructor);
    if(dlist_empty(l)){
        l->head = new_node;
        l->tail = new_node;
    }else{
        new_node->next = l->head;
        l->head->prev = new_node;
        l->head = new_node;
    }
    l->size++;
}

void dlist_append(dlist_t* l, void* data){
    dlist_node_t* new_node = dlist_new_node(data, l->constructor);
    if(dlist_empty(l)){
        l->head = new_node;
        l->tail = new_node;
    }else{
        l->tail->next = new_node;
        new_node->prev = l->tail;
        l->tail = new_node;
    }
    l->size++;
}

void dlist_remove(dlist_t* l, size_t i){
    if(!dlist_empty(l)){
        if(i == 0 || dlist_size(l) == 1){
            dlist_remove_head(l);
        }else if(i == dlist_size(l)-1){
            dlist_remove_tail(l);
        }else{
            dlist_iterator_t it = l->head;
            dlist_node_t* node;
            size_t k;
            for(k=0;k<i-1;k++){
                it = it->next;
            }
            node = it->next;
            it->next = node->next;
            node->next->prev = it;
            dlist_delete_node(node, l->destructor);
            l->size--;
        }
    }
}

void dlist_remove_head(dlist_t* l){
    if(!dlist_empty(l)){
        dlist_node_t* node = l->head;;
        if(dlist_size(l) == 1){
            l->head = NULL;
            l->tail = NULL;
        }else{
            l->head = l->head->next;
            l->head->prev = NULL;
        }
        dlist_delete_node(node, l->destructor);
        l->size--;
    }

}

void dlist_remove_tail(dlist_t* l){
    if(!dlist_empty(l)){
        dlist_node_t* node = l->tail;
        if(dlist_size(l) == 1){
            l->tail = NULL;
            l->head = NULL;
        }else{
            l->tail = l->tail->prev;
            l->tail->next = NULL;
        }
        dlist_delete_node(node, l->destructor);
        l->size--;
    }
}

void* dlist_access(dlist_t* l, size_t i){
    if(i == 0){
        return dlist_access_head(l);
    }else if(i == dlist_size(l)-1){
        return dlist_access_tail(l);
    }
    dlist_iterator_t it = l->head;
    size_t k;
    for(k=0;k<i;k++){
        it = it->next;
    }
    return it->data;
}

void* dlist_access_head(dlist_t* l){
    return l->head->data;
}

void* dlist_access_tail(dlist_t* l){
    return l->tail->data;
}

size_t dlist_size(dlist_t* l){
    return l->size;
}

size_t dlist_empty(dlist_t* l){
    return dlist_size(l) == 0 ? 1 : 0;
}