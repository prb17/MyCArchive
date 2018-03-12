all: prog4 

prog4: Alloc.o Memprint.o prog4.o AllocAns.o
	gcc -Wall -g -o prog4 Alloc.o Memprint.o prog4.o AllocAns.o

Alloc.o: Alloc.h Alloc.c
	gcc -Wall -g -c Alloc.c

