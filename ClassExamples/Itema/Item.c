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


	//Don't do this, bad pie
/*
	struct Item_t retval;
	retval.cost = 0;
	retval.weight = 0.0;
	retval.name = NULL;
	return &retval;
*/
}

struct Item_t * shallowCopy(struct Item_t *source)
{
	struct Item_t *retval = createItem();

	memcpy(retval, source, sizeof(struct Item_t));
	return retval;
}
struct Item_t * copyItem(struct Item_t *source)
{
	struct Item_t *retval = createItem();

	retval->cost = source->cost;
	retval->weight = source->weight;
	//retval->name = source->name;
	assignName(retval, source->name);
	return retval;
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
		free(this->name);
		this->name = NULL;
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
	//<name>: $<cost> <weight>lbs.\n
	fprintf(where, "%s: $%d %f\n", this->name, this->cost, this->weight);


}
/*
public class Item
{
	int cost;

	void setCost(int amt)
	{
		cost = amt;
	}
}
*/


