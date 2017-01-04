#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"memory_alloc.h"

//size of mementry is 32
//size of heap is 32760

int main(int argc, char ** argv){
	
	//Arrays of pointers to data that will be be malloced	
	
	int * array_int[5];
	char * array_str[5]; 
	float *	array_float[5];
	
	//mallocs for pointers in arrays
	printf("Size of a Mementry is 32 bytes. Size of the heap is 32760 bytes.\n\n");
	printf("Mallocing char, int and float values in that order.\n");
	array_str[0] = (char*) myMalloc(sizeof(char) * 40);		
	array_int[0] = (int*) myMalloc(sizeof(int));
	array_float[0] = (float*) myMalloc(sizeof(float));
	array_str[1] = (char*) myMalloc(sizeof(char) * 100);	
	array_int[1] = (int*) myMalloc(sizeof(int));
	array_float[1] = (float*) myMalloc(sizeof(float));
	array_str[2] = (char*) myMalloc(sizeof(char) * 500);	
	array_int[2] = (int*) myMalloc(sizeof(int));
	array_float[2] = (float*) myMalloc(sizeof(float));
	array_str[3] = (char*) myMalloc(sizeof(char) * 10);
	array_int[3] = (int*) myMalloc(sizeof(int));
	array_float[3] = (float*) myMalloc(sizeof(float));
	array_str[4] = (char*) myMalloc(sizeof(char) * 1000);
	array_int[4] = (int*) myMalloc(sizeof(int));
	array_float[4] = (float*) myMalloc(sizeof(float));

	//Setting array pointers equal to actual values
	
	
	strcpy(array_str[0] , "First str");
	strcpy(array_str[1] , "Second str");
	strcpy(array_str[2] , "Third str");
	strcpy(array_str[3] , "Fourth str");	
	strcpy(array_str[4] , "Fifth str");
	
	*array_int[0] = 123;
	*array_int[1] = 234;
	*array_int[2] = 345;
	*array_int[3] = 1;
	*array_int[4] = 12;

	*array_float[0] = 1.23;
	*array_float[1] = 23.4;
	*array_float[2] = 345.;
	*array_float[3] = 1.00;
	*array_float[4] = 1.2;
	
	//prints out values in the order that they were malloced to see if they contain correct value	
		
	int length = 5;
	int i = 0;
	printf("Values of malloced data\n");
	while(i<length){
		printf("String%d value:%s\n", i, array_str[i]);	
		printf("Int%d value:%d\n", i, *array_int[i]);
		printf("Float%d value:%f\n", i, *array_float[i]);
		i++;
	} //printing to confirm memory not corrupted
	printf("\n");
		
	//printing heap to check if memory blocks have been correctly allocated	
		
	printHeap();	
	printf("\n");

	//Freeing values to test myFree function

	//Testing Freeing a block with a prev free block and a succ free block
	//Frees first block that contains First str
	myFree(array_str[0]);
	printf("\n");
	printf("Heap after freeing first block\n");
	printHeap();
	printf("\n");
	
	//Frees third block that contains 1.23
	myFree(array_float[0]);
	printf("\n");
	printf("Heap after freeing third block\n");
	printHeap();
	printf("\n");
	
	//Frees Second block that contains 123. First, second, and third block should be merged.
	myFree(array_int[0]);
	printf("\n");
	printf("Heap after freeing second block. First, second and third blocks should merge.\n");
	printHeap();
	printf("\n");
	
	//Tests freeing a block with a free prev block	
	//Frees current second block. Should merge first and second blocks.
	myFree(array_str[1]);
	printf("\n");
	printf("Heap after freeing current second block. First and second blocks should merge.\n");
	printHeap();
	printf("\n");
	
	//Tests freeing a block with a free succ block
	//Frees current fourth block that contains Third str and third block that contains 23.4. Should merge fourth and third blocks.
	
	myFree(array_str[2]);
	myFree(array_float[1]);
	printf("\n");
	printf("Heap after freeing fourth and third blocks. Fouth and third blocks should merge.\n");
	printHeap();
	printf("\n");
		
	//Tests if placing objects into freed memory blocks
	//Calls malloc to request space that will be small enough to go in block 3 and cause subdivison of that block
	char *newThird = myMalloc(sizeof(char) * 400); 
	strcpy(newThird, "New string in third");
	printf("Heap after mallocing a space that is smaller than third block and will cause the third block to be subdivided.\n");	
	printf("\n");
	printHeap();
	printf("\n\n");	
	printf("String in third block: %s\n\n", newThird); //Printing strings to confirm that memory has not been corrupted
	
	//Calls malloc again to request a space that is smaller than size of first block but not small enough to require the first block to be subdivided
	char * newFirst = myMalloc(sizeof(char) * 200); 	
	strcpy(newFirst, "New string in first");
	printf("\n");
	printf("Heap after mallocing a space smaller than size of the first block but large enough to not cause subdivision of the first block.\n");
	printHeap();
	printf("\n\n");
	printf("String in first block: %s\n\n", newFirst);

	//Reprints non freed items in arrays to test if memory has not been corrupted
	printf("Printing ints that were not freed\n");
	i = 1;	
	while(i<length){
		printf("Int%d value:%d\n", i, *array_int[i]);
		i++;
	}
	i = 2;
	printf("Printing floats that were not freed\n");
	while(i<length){
		printf("Float%d value:%f\n", i, *array_float[i]);
		i++;
	} 
	i = 3;	
	printf("Printing strings that were not free\n");
	while(i<length){
		printf("String%d value:%s\n", i, array_str[i]);
		i++;
	} 	
	printf("Printing malloced strings from before\n%s\n%s\n\n", newFirst, newThird);
	return 0;
}
