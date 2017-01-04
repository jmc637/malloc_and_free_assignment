#define myMalloc(x) myMalloc_(x, __FILE__, __LINE__)
#define myFree(x) myFree_(x, __FILE__, __LINE__)

typedef struct memEntry_ memEntry;


struct memEntry_{
	memEntry * prev, * succ;
	int isFree;
	unsigned int size;
	int recognition; //Recognition pattern is 0xAAAAAAAA for non free entries
};

void * myMalloc_(unsigned int size, const char * file, unsigned int line); //use myMalloc(unsigned int size) in actual main functions

void myFree_(void * p1, const char * file, unsigned int line); //use myFree(unsigned int size) in actual main functions

void printHeap();
