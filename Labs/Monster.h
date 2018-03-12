#ifndef MONSTER_H
#define MONSTER_H
#include<stdlib.h>
#include<stdio.h>

struct Monster_t
{
  char *name;
  int energy;
  size_t status;
} Monster_t;

struct Monster_t* constructMonster();
struct Monster_t* destroyMonster();

void basicPrintMonster(FILE*, struct Monster_t*);

void setName(struct Monster_t*, char*);
char* getName(struct Monster_t*);

void setEnergy(struct Monster_t*, int);
int getEnergy(struct Monster_t*);

void setStatus(struct Monster_t*, char*);
void getStatus(struct Monster_t*, char*);

#endif
