/* Slighted modified LinkedList C implementation from Wikipedia */

#include <stdio.h> /* for printf */
#include <stdlib.h> /* for malloc */
#include "linkedList.h"




// **Functions **

// Add to the head of the given linkedlist
LLIST *list_add(LLIST **p, huf *i) {
	if (p == NULL){
		return NULL;
	}
	LLIST *n = malloc(sizeof(LLIST));
	if (n == NULL){
		return NULL;
	}
	n->next = *p; /* the previous element (*p) now becomes the "next" element */
	*p = n; /* add new empty element to the front (head) of the list */
	n->data = i;
	return *p;
}

// Remove the head of the given linkedlist

void list_remove(LLIST **p) {
	if (p != NULL && *p != NULL) {
		LLIST *n = *p;
		*p = (*p)->next;
		free(n);
	}
}


//our remove
/**
LLIST *list_remove(LLIST *p){
	if(p->next != NULL){
		p = p->next;
	}
	else{
		p = NULL;
	}
	return p;
}
*/
// Find the node in the list and return it
LLIST **list_search(LLIST **n, huf *i) {
	if (n == NULL){
		return NULL;
	}
	while (*n != NULL) {
		if ((*n)->data->c == i->c) {
			return n;
		}
	n = &((*n)->next);
	}
	return NULL;
}

// Display the list
/*
void list_print(LLIST *n) {
	printf("[");
	while (n != NULL) {
		printf(" %d (%p -> %p) --", n->data, n, n->next);
		n = n->next;
	}
	printf("]\n");
}
*/
//method that inserts a tnode into the linked list sorted by weight
void list_add_in_order(LLIST **p, huf *i){
	if(p==NULL){
		return NULL;
	}
	
	LLIST *n = malloc(sizeof(LLIST));
	if(n==NULL){
		return NULL;
	}
	n->data = i; 
	if(*p==NULL||(*p)->data->weight >= i->weight){
		n->next = *p;
		*p=n;
	}else{
		LLIST *c = *p;
		while(c ->next != NULL && c->next->data->weight< i->weight){
			c=c->next;
		}
		n->next = c->next;
		c->next=n;
	}
	return *p;
	
			
	
	
	
	}
	
	/*LLIST* newNode = (LLIST*) malloc(sizeof(LLIST));
	newNode->data = i;
	newNode->next = NULL;
	LLIST* previous;
	LLIST* current = *n;
	if(*n == NULL || current->data.weight >= i.weight){
		newNode->next = *n;
		*n = newNode;
	}
	else{
		while(current->next != NULL && current->next->data.weight <= i.weight){
			previous = current;
			current = current->next;	
		}
		newNode->next = current->next;
		current->next = newNode;	
		
		*/
		
	

	
	
	
	/*LLIST* head = *n;//head of list
	if (head == NULL){
		head->data = i;
	}
	
	LLIST *newNode;//new node to be injected forcefully into list
	newNode = malloc(sizeof(LLIST));//mallocing space for list
	newNode->data = i;//setting tnode to data part of node
	if (newNode->data.weight <= head->data.weight){//if data to be added is less then the head
		list_add(n, i);//use add method
	}
	LLIST *temp;//pointer to current pos in list
	LLIST *prev;//pointer to prev pos in list
	temp = head->next;//moving temp to the second thing in the list
	prev = head;//moving prev to head of list
	while (temp != NULL && temp->data.weight < newNode->data.weight) {
		prev = temp;//moving pre pointer down the list
		temp = temp->next;//moving temp to the following pos in list
	}
	newNode->next = temp;//setting newNode to the current pos
	prev->next = newNode;//setting prevs next to newNode*/
	

