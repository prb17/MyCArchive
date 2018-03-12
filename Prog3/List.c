/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Structing items in a List
  Program #3
 */

#ifndef LIST_C
#define LIST_C
#include"List.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int spaceNeeded(int num)
{
  if (num == 0)
    {
      return 1;
    }
  
  int digitSize = 0;
  while(num != 0)
    {
      num /= 10;
      digitSize++;
    }
  return digitSize;
}

struct Node* constructList(int newValue)
{
  struct Node *newNode;
  newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->value = newValue;
  newNode->nextNode = NULL;
  return newNode;
}

struct Node* destroyList(struct Node *startNode)
{
  if (startNode == NULL)
    {
      return NULL;
    }
  struct Node* next = startNode->nextNode;
  if (next == NULL)
    {
      free(startNode);
      startNode = NULL;
      return NULL;
    }
  free(startNode);
  startNode = NULL;  
  return destroyList(next);
}

size_t size(struct Node *startNode)
{
  size_t nodeCounter = 0;
  struct Node *currentNode = startNode;
  while(currentNode->nextNode != NULL)
    {
      currentNode = currentNode->nextNode;
      nodeCounter++;
    }
  nodeCounter++;
  return nodeCounter;
}

struct Node* insert(struct Node *startNode, int newValue)
{
  if(startNode == NULL)
    {
      return constructList(newValue);
    }
  else
    {
      struct Node* currentNode = startNode;
      while(currentNode->nextNode != NULL)
	{
	  currentNode = currentNode->nextNode;
	}
      currentNode->nextNode = constructList(newValue);
      return startNode;
    }
}

int find(struct Node *startNode, int searchValue)
{  
  struct Node *currentNode = startNode;
  while(currentNode->nextNode != NULL)
    {
      if(currentNode->value == searchValue)
	{
	  return 1;
	}
      currentNode = currentNode->nextNode;
    }
  if(currentNode->value == searchValue)
    {
      return 1;
    }
  return 0;
}

int traverse(struct Node *startNode, char *listItems)
{
  if (startNode == NULL)
    {
      return 0;
    }
  struct Node *currentNode = startNode;
  int *nodeValues = (int *)malloc(size(startNode) * sizeof(int));
  int index = 0;

  while(currentNode->nextNode != NULL)
    {
      nodeValues[index] = currentNode->value;
      index++;
      currentNode = currentNode->nextNode;
    }
  nodeValues[index] = currentNode->value; //the last node still needs
                                          //to be counted
  int listLength = size(startNode);
  index = 0;
  while(index < listLength-1)
    {
      char *numStr = (char *)malloc(spaceNeeded(nodeValues[index]) * sizeof(char));
      sprintf(numStr, "%d", nodeValues[index]);
      strcat(listItems, numStr);
      strcat(listItems, ", ");
      index++;
      free(numStr);
      numStr = NULL;
    }
  char *numStr = (char *)malloc(spaceNeeded(nodeValues[index]) * sizeof(char));
  sprintf(numStr, "%d", nodeValues[index]);
  strcat(listItems, numStr);

  free(numStr);
  numStr = NULL;
  free(nodeValues);
  nodeValues = NULL;
  return 1;
}

struct Node* removeItem(struct Node *startNode, int removeValue)
{
  if (startNode == NULL)
    {
      return NULL;
    }
  struct Node *startingNode = startNode;
  struct Node *currentNode = startNode;
  struct Node *previousNode = NULL;
  while(currentNode->nextNode != NULL)
    {
      if(currentNode->value == removeValue)
	{
	  if(startingNode == currentNode)
	    {
	      startingNode = startingNode->nextNode;
	      free(currentNode);
	      currentNode = startingNode;
	    }
	  else
	    {
	      previousNode->nextNode = currentNode->nextNode;
	      free(currentNode);
	      currentNode = previousNode->nextNode;
	    }
	}
      else
	{
	  previousNode = currentNode;
	  currentNode = currentNode->nextNode;
	}
    }
  return startingNode;
}

char* traverse2(struct Node *startNode)
{
  if (startNode == NULL)
    {
      return "0";
    }
  struct Node *currentNode = startNode;
  int *nodeValues = (int *)malloc(size(startNode) * sizeof(int));
  int index = 0;
  while(currentNode->nextNode != NULL)
    {
      nodeValues[index] = currentNode->value;
      index++;
      currentNode = currentNode->nextNode;
    }
  nodeValues[index] = currentNode->value; //the last node still
                                          //needs
                                          //to be counted
  
  int listLength = size(startNode);
  char *listItems = (char *)malloc((3*listLength-2) * sizeof(char));
  index = 0;
  listItems[0] = '\0';
  
  while(index < listLength-1)
    {
      int x = 0;
      x += 1;
      char *numStr = (char *)malloc(spaceNeeded(nodeValues[index]) * sizeof(char));
      sprintf(numStr, "%d", nodeValues[index]);
      strcat(listItems, numStr);
      strcat(listItems, ", ");
      index++;
      free(numStr);
      numStr = NULL;
    }
  char *numStr = (char *)malloc(spaceNeeded(nodeValues[index]) * sizeof(char));
  sprintf(numStr, "%d", nodeValues[index]);
  strcat(listItems, numStr);

  free(numStr);
  numStr = NULL;
  free(nodeValues);
  nodeValues = NULL;
  
  
  return listItems;
}
#endif
