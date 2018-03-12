/*
  Group 9
  Konka Simon Peter
 */

#include<stdio.h>
#include<stdlib.h>
#include"Monster.h"

int main(int argc, char **argv)
{
  struct Monster_t *it = createMonster();

  setName(it, "Bob");
  basicPrintMonster(stdout, it);
  
  return 0;
}

