#include "linkedList.h"
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//test for array
void printArrayTest(huf* ascii){
	for(int i = 0; i< 128; i++){//walks the array 
			if(ascii[i].weight != 0){//just shortens the test print up 
			int dub = ascii[i].weight;//grabs the weight
			//char c = (char) ascii[i].c - '0';
			printf("ascii[%d]: weight = %d, data = %c\n", i, dub, ascii[i].c);//tells us what the weight is. 
		}
	}
	printf("\n");
}

//test for linked list
void printListTest(LLIST* ascii){
	LLIST* current = ascii;//new node for the list
	int count = 0; 
	if (current != NULL){
		while(count<128){
			printf("list weight %lf, data %c\n", current->data->weight, current->data->c);
			current=current->next;
			count++;
		}
	}
}

//tests 2 array
void printArrayTest2(huf* ascii){
	for(int i = 0; i < 128; i++){
		int dub = ascii[i].weight;
		//char c = (char) ascii[i].c - '0';
		printf("ascii[%d]: weight = %d, data = %c\n", i, dub, ascii[i].c);
	}
	printf("\n");
}

//method to create array of tnodes
huf* createFreqTable(char *text){
	FILE* fIn = fopen(text, "r");
	huf* ascii = (huf*)malloc(128 * sizeof(huf));
	int i = 0;
	//initalizing all points in the array to zero
	while (i < 128){
		ascii[i].left = NULL;
		ascii[i].parent = NULL;
		ascii[i].right = NULL;
		ascii[i].weight = 0;
		ascii[i].c = i;
		i++;
	}
	//printArrayTest2(ascii);
	int val = fgetc(fIn);
	//counting the number of times a character occurs in the given file
	while(val != EOF){
		ascii[val].weight = ascii[val].weight + 1;
		val = fgetc(fIn);
		}
	//counts the end of file point as only one, there will only be one end of file point
	ascii[128].weight = ascii[128].weight + 1;
	//printArrayTest(ascii);
	return ascii;
}

//helper method to create list
LLIST* createList(huf* leafNodes){
	//LLIST** list =(LLIST**) malloc(128 * sizeof(LLIST));
	LLIST *list = NULL;
	for(int i = 0; i < 128; i++){
		list_add_in_order(&list, &leafNodes[i]);
	}
	//printListTest(list);
	return list;
}

//method to create huffman tree
huf* createHuffmanTree(huf* leafNodes){
	LLIST* list = createList(leafNodes);
	while(list->next != NULL ){
		huf *alpha = list->data;
		huf *beta = list->next->data;
		//check these lines if there are bugs latter
		huf *temp = (huf*) malloc(sizeof(huf));//
		temp->c = -1;
		temp->weight = alpha->weight + beta->weight;
		temp->left = alpha;
		//printf("temp weight: %lf\n", temp->weight);
		temp->right = beta;
		temp->parent = NULL;
		alpha->parent = temp;
		beta->parent = temp;
		list_remove(&list);
		list_remove(&list);
		list_add_in_order(&list, temp);
	}
	//printf("root weight %lf\n", list->data->weight);
	return list->data;
}

//encode method
void encodeFile(FILE* p, huf* leafNode){
	FILE* fp = fopen(p,"r");
	FILE* output = fopen(strcat(p,".huff"), "w");
	FILE* out = fopen("second.txt","w+");
	char temp;
	int c = fscanf(fp, "%c", &temp);
	//printf("c act: %c\nc exp: b\n" , c);
	
	//printf("%d\n", c);
	
    char* string = (char*) malloc(8*sizeof(char));
	int count = 0; 
 	while(c != EOF){
		int num = temp;
		huf* tn = &leafNode[num];
		//printf("value: %c\n", tn->c);
		//printf("value: %lf\n", tn->parent->weight);
		while(tn->parent!= NULL){//while you are not at the parent. 
			if(tn->parent->right == tn){//am i the right child. 
				string[count] = '1';//get 1
			}
			else{//i am the left child. 
				string[count] = '0';
			}
			count++;		
			tn = tn->parent;//going to the parent. 
			if(count == 8){//loop to write out the file. 
				for(int i = 0; i < 8; i++){
					fprintf(out,"%c",string[i]);
				}
				count=0;
			}//closes count if statement
		//printf("c act: %c\n" , c);
		}
		c = fscanf(fp, "%c", &temp);
	}
	if(count != 0){
		for(int z = count; z >= 0; z--){
				fprintf(out,"%c",string[z]);
		}
	}
	fseek(out,-1L,2);
	//printf("number of char to be copied %li\n", ftell(out));
	long position = ftell(out);
	position++;
	char character;
	while(position){//this loop reverses the file. 
		character= fgetc(out);
		fputc(character,output);
		fseek(out,-2L,1);
		position--;
	}
	
	//printf("actu: %d\nexpected: 16\n", test);
	fclose(out);
	fclose(output);
	fclose(fp);
}
//this decodes the file then reverses it so it is in the right order
void decodeFile(FILE* p, huf* treeRoot){
	FILE* in = fopen(p, "r");//openin the file
	FILE* out = fopen("dereverse.txt","r+");//making the output file in reverseFile
	FILE* reverseFile = fopen(strcat(p,".dec"), "w");//making a file to output in the correct order. 
	if(in==NULL||out==NULL){//if the files are null out put nice message 
		printf("Error executing\n");
		fflush(stdout);
		exit(1);
	}
	int isEOF; 
	char temp;
	huf* current = treeRoot;
	do{//do while looop
		isEOF=fscanf(in,"%c",&temp);//gets new char from file. 
		if(temp=='1'){//if it is a one go right. 
			current = current->right;//moving right. 
		}
		else{//else go left.
			current=current->left;//going left. 
		}
		if(current->c != -1){ // if it is not an inner node. 
			fputc(current->c,out);// sending the char. 
			current = treeRoot;//resetting the node. 
		}
	}while(isEOF != EOF);//while you aren't at the end of a file. 
	fseek(out,-1L,2);
	//printf("number of caracters to be copied %li\n", ftell(out));
	long position = ftell(out);
	position++;
	char character;
	while(position - 7 ){//this loop reverses the loop back into the right order. and -7 because it is broke otherwise....
		character = fgetc(out);
		fputc(character, reverseFile);
		fseek(out,-2L,1);
		position--;
	}
	fclose(reverseFile);
	fclose(in);
	fclose(out);
}
	



//main method of hcompress.c
int main(int argc, char *argv[]) {
	// Check the make sure the input parameters are correct
	if (argc != 3) {
		printf("Error: The correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf\"\n"); fflush(stdout);
		exit(1);
	}
	//FILE* fp = fopen(argv[2], "r");
//printf(argv[2]);	
	huf* leafNodes = createFreqTable("decind.txt");// Create the frequency table by reading the generic file
	huf* treeRoot = createHuffmanTree(leafNodes);// Create the huffman tree from the frequency table
	
	if (strcmp(argv[1], "-e") == 0) {// encode
		encodeFile(argv[2], leafNodes);// Pass the leafNodes since it will process bottom up
	} 
	else { // decode
		// Pass the tree root since it will process top down
		decodeFile(argv[2], treeRoot);
	}

	return 0;
}

