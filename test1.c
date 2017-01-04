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
	}
	printf("\n");
		
	//printing heap to check if memory blocks have been correctly allocated	
		
	printHeap();	
	printf("\n");

	//Mallocing a value that wont fit in heap to test what happens
	
	printf("Mallocing a string tooBig that can't fit in heap\n");
	char * tooBig = (char*)myMalloc(sizeof(char) * 31000);
	
	if(tooBig == NULL){
		printf("Pointer of tooBig set to NULL\n");	
	}
	else{
		printf("Pointer of tooBig not set to NULL\n");	
	}
	printf("\n");
	
	//reprinting heap to check memory blocks again
		
	printHeap();

	return 0;
}
