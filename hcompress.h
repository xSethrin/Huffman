#include <stdio.h> 
#include <stdlib.h>

typedef struct tnode {
	double weight;
	int c;
	struct tnode* left;
	struct tnode* right;
	struct tnode* parent;
} huf;

//Prototypes
/*struct tnode* createFreqTable(FILE f);
void createHuffmanTree(huf* tn);
void encodeFile(FILE f, huf* tn);
void decodeFile(FILE f, huf* tn);*/
