#include<stdio.h>
#include<stdlib.h>
#include"memory_alloc.h"

#define block_Size 32760
#define fudgeFactor 20 //This factor is used to prevent the heap from being divided up into chunks that are too small.


static char big_Block[block_Size]; //This is memory set aside for heap.
static int initialized = 0;
static memEntry * root;

void * myMalloc_(unsigned int size, const char * file, unsigned int line){
	
	memEntry * prev, * succ, *p;
	
	if(!initialized){
		root = (memEntry*) big_Block;
		root->prev = NULL;
		root->succ = NULL;
		root->size = block_Size - sizeof(memEntry);		
		root->isFree = 1;
		root->recognition = 0xAAAAAAAA;
		initialized = 1;
	} //For first call to myMalloc. 

	p = root;
	
	while(p!= NULL){
		if(p->size < size){
			p = p->succ;		
		}	
		else if(!p->isFree){
			p = p->succ;	
		}
		else if(p->size < (size + sizeof(memEntry) + fudgeFactor)){
			p->isFree = 0;
			p->recognition = 0xAAAAAAAA;
			return (char *)p + sizeof(memEntry);
		}
		else{
			succ = (memEntry*)((char*)p + sizeof(memEntry) + size);
			succ->prev = p;
			succ->succ = p->succ;
			if(p->succ != NULL){
				p->succ->prev = succ;			
			}		
			p->succ = succ;
			succ->size = p->size -sizeof(memEntry) - size;
			p->size = size;
			succ->isFree = 1;
			p->isFree = 0;
			p->recognition = 0xAAAAAAAA;
			succ->recognition = 0x87634521; //Change recognition code to this to prevent already free blocks from being freed
			return (char *)p + sizeof(memEntry);
		}
	} //Similar to algorithm used in class. Further explanation in readme.

	printf("Not enough memory space for request. Returned NULL pointer.\nCall made in File: %s Line: %d\n",file, line); //Error message and NULL pointer returned if memory request is larger than can be accomodated.
	return p;
}

void myFree_(void * p, const char * file, unsigned int line){
	memEntry * ptr, * prev, * succ;
	ptr = (memEntry*)p - 1;
	prev = ptr->prev;
	succ = ptr->succ;
	if(ptr->recognition != 0xAAAAAAAA){
		printf("Attempting to free invalid pointer. Did not free.\nCall made in File: %s Line: %d\n", file, line);
		return;	
	} //Attempting to free invalid pointer. Returns error message.
	if((prev != NULL && succ != NULL) && prev->isFree && succ->isFree){
		prev->size += (2 * sizeof(memEntry)) + ptr->size + succ->size;
		prev->succ = succ->succ;
		if(succ->succ != NULL){
			succ->succ->prev = prev;		
		}
		ptr->recognition = 0X87634521;	
	} //Prev, succ, and ptr memory space are free. Merge them.
	else if((prev != NULL) && prev->isFree){
		prev->size += sizeof(memEntry) + ptr->size;
		prev->succ = succ;
		if(succ != NULL){
			succ->prev = prev;		
		}	
		ptr->recognition = 0X87634521;	
	} //Prev and ptr memory space free. Merge them.
	else if((succ != NULL) && succ->isFree){
		ptr->size += sizeof(memEntry) + succ->size;
		ptr->succ = succ->succ;
		if(succ->succ != NULL){
			succ->succ->prev = ptr;		
		}	
		ptr->isFree = 1;
		ptr->recognition = 0X87634521;	
	} //Succ and ptr memory space free. Merge them.
	else{
		ptr->isFree = 1;
		ptr->recognition = 0X87634521;
	} //Neither succ or prev memory space free. No merging.
} //Similar algorithm as used in class. Further explanation in readme.

//Function for printing heap used in debugging and testing.
void printHeap(){
	int i = 1;	
	if(!initialized){
		printf("Heap is not initialized\n");	
	}
	printf("Heap Memory Block Info\n");
	memEntry * ptr = root;
	while(ptr != NULL){
		if(ptr->isFree){
			printf("Size of memory block %d:%d\tFree:Y\tRec Pat:0x%x\n", i, ptr->size, ptr->recognition);			
		}
		else{
			printf("Size of memory block %d:%d\tFree:N\tRec Pat:0x%x\n", i, ptr->size, ptr->recognition);
		}
		ptr = ptr->succ;	
		i++;
	}	
}
