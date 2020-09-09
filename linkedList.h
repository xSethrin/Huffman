// Structures and typedefs
#include "hcompress.h"
#include <stdio.h> 
#include <stdlib.h>

typedef struct node {
	huf *data;
	struct node *next; /* pointer to next element in list */
} LLIST;

// Prototypes
LLIST *list_add(LLIST **p, huf *i);
void list_remove(LLIST **p);
//LLIST *list_remove(LLIST *p);
LLIST **list_search(LLIST **n, huf *i);
void list_print(LLIST *n);
void list_add_in_order(LLIST **n, huf *i);