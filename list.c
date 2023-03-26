#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* L = (List*) malloc(sizeof(List));
  if(L==NULL) exit(EXIT_FAILURE);
  L->head=NULL;
  L->tail=NULL;
  L->current=NULL;

  return L;
}

void * firstList(List * list) {
  if (!list->head){
    return NULL;
  }
  else 
    list->current=list->head;
  
  return list->head->data;
}

void * nextList(List * list) {
  if(list->current==NULL){
    return NULL;
  }
  if(list->current->next==NULL){
    return NULL;
  }
    
  list->current=list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if(!list->tail){
    return NULL;
  }
  else
    list->current=list->tail;
    
  return list->tail->data;
}

void * prevList(List * list){
  if(list->current==list->head || !list->current)
    return NULL;
  else
    list->current = list->current->prev;  
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node * Newnodo = createNode(data);
  if(!list->head){
    list->head=Newnodo;
    list->current=Newnodo;
    list->tail=Newnodo;
  }
  else{
    Newnodo->next=list->head;
    list->head=Newnodo;
  }
  
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * N_nodo = createNode(data);
  if(!list->head){
    list->head=N_nodo;
    list->current=N_nodo;
    list->tail=N_nodo;
  }
  else{
    N_nodo->prev=list->current;
    N_nodo->next=list->current->next;
    list->current->next=N_nodo;
    if(list->current==list->tail)
      list->tail=N_nodo;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if(!list->head) return NULL;
  Node * aux = list->current;
  void * auxdata = aux->data; 
  if(list->current==list->head){
    list->head=aux->next;
    list->head->prev=NULL;
  }
  else{
    Node * nodaux = list->head;
    while(nodaux->next!=list->current)
      nodaux = nodaux->next;
    nodaux->next=list->current->next;
  } 
  if(list->current==list->tail)
    list->tail=list->current->prev;
  list->current=aux->next;
  free(aux);
  return auxdata;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}