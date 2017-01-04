#include<stdio.h>
#include<stdlib.h>
#include"memory_alloc.h"

//size of mementry is 32
//size of heap is 32760

int main(int argc, char ** argv){
	
	//Arrays of pointers to data that will be be malloced	
	int * array_int[5];
	
	//mallocs for integers
	printf("Size of a Mementry is 32 bytes. Size of the heap is 32760 bytes.\n\n");
	printf("Mallocing int values.\n\n");	
	array_int[0] = (int*) myMalloc(sizeof(int));	
	array_int[1] = (int*) myMalloc(sizeof(int));	
	array_int[2] = (int*) myMalloc(sizeof(int));
	array_int[3] = (int*) myMalloc(sizeof(int));
	array_int[4] = (int*) myMalloc(sizeof(int));
	
	//printing heap
	printf("Heap after mallocing space for 5 individual ints.\n");
	printHeap();
	printf("\n\n");	
	
	//Assigning values to int pointers
	*array_int[0] = 0;	
	*array_int[1] = 1;	
	*array_int[2] = 2;
	*array_int[3] = 3;
	*array_int[4] = 4;

	
	//Testing double free error checking
	myFree(array_int[0]);
	printf("Heap after freeing int 0.\n");
	printHeap();
	printf("\n\n");		
	
	//attempting to double free
	printf("Trying to free pointer to first block in heap again.\n");	
	myFree(array_int[0]);
	printf("\n");
	
	myFree(array_int[1]);
	printf("Heap after freeing int 1.\n");
	printHeap();
	printf("\n\n");
	
	printf("Trying to free pointer to second block in heap again.\n");
	myFree(array_int[1]);
	
	//attempting to Free values outside of heap
	
	int randomInt = 12;
	float randomFloat = 1.2;
	char * randomWord = "random word";
	
	printf("\n\nAttempting to free values outside heap.\n");
	myFree(&randomInt);
	myFree(&randomFloat);
	myFree(randomWord);	
	
	//attempting to free pointers inside heap but were not returned by malloc
	int * incorrect2 = array_int[2] + 5;
	int * incorrect3 = array_int[3] - 4;
		
	printf("\n\nAttempting to free values inside heap that were not returned by malloc.\n");
	myFree(incorrect2);
	myFree(incorrect3);
	
	//Freeing same pointer but should be valid in this case since pointer is malloced again before being freed
	array_int[0] = (int*) myMalloc(sizeof(int));
	//Should use first chunk in heap but no subdivision should occur because of size of the memEntry and fudge factor
	printf("\n\nHeap after malloc call that uses first block in heap.\n");
	printHeap();
	printf("\n\n");
	
	myFree(array_int[0]);
	printf("Heap after refreeing pointer.\n");
	printHeap();
	
	return 0;
}
