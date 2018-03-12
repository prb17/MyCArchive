#include"Item.h"
#include<stdlib.h>
#include<string.h>

struct Item_t * createItem()
{
	struct Item_t *retval;
	retval = (struct Item_t *)malloc(sizeof(struct Item_t));

	retval->cost = 0;
	retval->weight = 0.0;
	retval->name = NULL;
	return retval;

/*
	//This is bad, don't do:
	struct Item_t bad;
	bad.cost = 0;
	bad.weight = 0.0;
	bad.name = NULL;
	return &bad;
*/

}

struct Item_t * destroyItem(struct Item_t * it)
{
	//Order matters.
	free(it->name);

	free(it);
	return NULL;
}

//struct Item_t *createItem(int cost)
//{
//	struct Item_t *retval = createItem();
//	retval->cost = cost;
//	return retval;
//}

void assignName(struct Item_t * this, char *name)
{
	if(this)
	{
		this->name = (char *)malloc((strlen(name)+1) * sizeof(char));
		strcpy(this->name, name);
	}
}

void setCost(struct Item_t *this, int cost)
{
	if(this)
	{
		this->cost = cost;
	}
}

int getCost(struct Item_t *this)
{
	return this->cost;
}

void printItem(struct Item_t *this, FILE* where)
{
	//<name>: $<cost> <weight>lbs
	fprintf(where, "%s: $%d %flbs\n", this->name, this->cost, this->weight);

}
