#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include"Item.h"

int main(int argc, char **argv)
{
	//Java-style, probably not what you want:
//	struct Item_t thing;
//	thing.cost = 15;

	//More appropriate pointer style:
//	struct Item_t *it = (struct Item_t *)malloc(sizeof(struct Item_t));
//	(*it).cost = 0;
//	it->weight = 0.0;
//	it->name = NULL;

	//More appropriate pointer style:

	struct Item_t *it = createItem();
	assignName(it, "Bob");

//	printItem(it, stdout);
//	printItem(it, stderr);

	setCost(it, 15);
//	printItem(it, stdout);
	setCost(it, 40);
//	printItem(it, stderr);

	FILE *outFile = fopen("afternoon.txt", "w+");
	if(outFile == NULL)
	{
		fprintf(stderr, "Error opening file\n");
		fprintf(stderr, "%d: %s\n", errno, strerror(errno));

		return 1;
	}
//	printItem(it, outFile);
	fclose(outFile);

//	struct Item_t *shallow = shallowCopy(it);
	struct Item_t *copy = copyItem(it);
	assignName(it, "Alice");
//	it->name[0] = 'A';
//	printItem(shallow, stdout);
	printItem(copy, stdout);
	printItem(it, stdout);

	copy = destroyItem(copy);
//	shallow = destroyItem(shallow);
	it = destroyItem(it);
//	free(it);

	//struct Item_t stack = *createItem();
/*	struct Item_t stack;
	stack.name = NULL;
	stack.cost = 0;
	stack.weight = 0.0;

	assignName(&stack, "Rick");
	destroyItem(&stack);
*/
	return 0;
}
