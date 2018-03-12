#ifndef ITEM_H
#define ITEM_H

#include<stdio.h>

struct Item_t
{
	int cost;
	double weight;
	char *name;
};

struct Item_t * createItem();
struct Item_t * shallowCopy(struct Item_t *);
struct Item_t * copyItem(struct Item_t *);
//struct Item_t * createItem(int cost);
struct Item_t * destroyItem(struct Item_t * it);

void assignName(struct Item_t *this, char *name);
void setCost(struct Item_t *this, int cost);

int getCost(struct Item_t *this);

void printItem(struct Item_t *this, FILE* where);

#endif
