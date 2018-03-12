all: lab5

lab5: lab5.o Monster.o
	gcc -Wall -g -o lab5 lab5.o Monster.o

Monster.o: Monster.h Monster.c
	gcc -Wall -g -c Monster.c

lab5.o: lab5.c
	gcc -Wall -g -c lab5.c
