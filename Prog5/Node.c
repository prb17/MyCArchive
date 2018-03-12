/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Single Linked List
  Program #5
*/

#ifndef NODE_C
#define NODE_C

#include"Node.h"
#include<string.h>
#include<stdlib.h>

struct Node* constructNode(char* newName, void* newData, int numElements)
{
  struct Node *node = (struct Node*)malloc(sizeof(struct Node));
  node->next = NULL;
  node->name = (char *)malloc((strlen(newName)+1) * sizeof(char));
  for(int i = 0; i < strlen(newName)+1; i++)
    {
      node->name[i] = newName[i];
    }
  node->data = newData;
  node->dataSize = numElements;
  return node;
}

struct Node* destroyNode(struct Node *node)
{
  free(node->name);
  node->next = NULL;
  free(node);
  node = NULL;
  return NULL;
}

#endif
