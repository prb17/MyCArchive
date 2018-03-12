#include"Monster.h"
#include<stdio.h>
#include<stdlib.h>

#ifndef MONSTER_C
#define MONSTER_C

struct Monster_t* createMonster()
{
  struct Monster_t* Monster;
  Monster = (struct Monster_t*)malloc(sizeof(struct Monster_t));

  Monster->name = "Noname";
  Monster->energy = 0;
  Monster->status = 0;
  return Monster;
}

struct Monster_t* destroyMonster(struct Monster_t* Monster)
{
  //free(name);
  free(Monster);
  return NULL;
}

void basicPrintMonster(FILE* output, struct Monster_t *Monster)
{
  fprintf(output, "%s: %d\n", Monster->name, Monster->energy);
}

void setName(struct Monster_t* Monster, char *newName)
{
  Monster->name = newName;
}
char* getName(struct Monster_t* Monster)
{
  return Monster->name;
}

void setEnergy(struct Monster_t* Monster, int E)
{
  Monster->energy = E;
}
int getEnergy(struct Monster_t* Monster)
{
  return Monster->energy;
}

void addStatus(struct Monster_t* Monster, size_t addedStatus)
{
  size_t newStatus  = (Monster->status | addedStatus);
  Monster->status = newStatus;
}
int removeStatus(struct Monster_t* Monster)
{
  
}


#endif
