all: useItem

useItem: useItem.o Item.o
	gcc -Wall -g -o useItem useItem.o Item.o

Item.o: Item.h Item.c
	gcc -Wall -g -c Item.c

useItem.o: useItem.c
	gcc -Wall -g -c useItem.c
