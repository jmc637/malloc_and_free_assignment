test1: test1.o memory_alloc.o
	gcc test1.o memory_alloc.o -o test1 -g

test2: test2.o memory_alloc.o 
	gcc test2.o memory_alloc.o -o test2 -g

test3: test3.o memory_alloc.o
	gcc test3.o memory_alloc.o -o test3 -g

test1.o: memory_alloc.c test1.c memory_alloc.h 
	gcc -c test1.c -g

test2.o: memory_alloc.c test2.c memory_alloc.h
	gcc -c test2.c -g

test3.o: memory_alloc.c test3.c memory_alloc.h
	gcc -c test3.c -g

memory_alloc.o: memory_alloc.c memory_alloc.h
	gcc -c memory_alloc.c -g

clean:
	rm -rf *.o test1 test2 test3
