/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Single Linked List
  Program #5
*/

#ifndef LISTFILE_C
#define LISTFILE_C

#include"ListFile.h"
#include"Node.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

struct ListFile* makeList()
{
  struct ListFile* list = (struct ListFile*)malloc(sizeof(struct ListFile));
  list->head = NULL;
  return list;
}

struct ListFile* copyList(struct ListFile* original)
{
  struct ListFile* copy = (struct ListFile*)malloc(sizeof(struct ListFile));
  copy->head = constructNode(original->head->name, original->head->data, original->head->dataSize);
  return copy;
}

struct ListFile* destroyList(struct ListFile* list)
{
  //traverse the list and destroy nodes
  struct Node *temp = list->head;
  while(list->head != NULL)
    {     
      list->head = list->head->next;
      destroyNode(temp);
      temp = list->head;
    }
  temp = NULL;
  free(list);
  return list = NULL;
}

void* findByName(struct ListFile* list, char* nameToMatch)
{
  struct Node* tempHead = list->head;
  void *matchedData = NULL;
  while(list->head != NULL)
    {
      if(strcmp(list->head->name, nameToMatch) == 0)
	{
	  matchedData = list->head->data;
	  break;
	}
    }
  list->head = tempHead;
  return matchedData;
}

int findByData(struct ListFile* list, void* dataToMatch, int numElements)
{
  int numOfMatchingElements = 0;
  struct Node* tempHead = list->head;
  while(list->head != NULL)
    {
      if(list->head->data == dataToMatch && list->head->dataSize == numElements)
	{
	  numOfMatchingElements++;
	}
      list->head = list->head->next;
    }
  list->head = tempHead;
  return numOfMatchingElements;
}

int removeByName(struct ListFile* list, char* nameToRemove)
{
  struct Node* tempHead = list->head;
  struct Node* prevHead = NULL;
  while(list->head != NULL)
    {
      if(strcmp(list->head->name, nameToRemove) == 0)
	{
	  prevHead->next = list->head->next;
	  destroyNode(list->head);
	  list->head = tempHead;
	  return 1;
	}
      prevHead = list->head;
      list->head = list->head->next;
    }
  list->head = tempHead;
  return 0;
}

int removeByData(struct ListFile* list, void* dataToRemove, int numElements)
{
  int elementsRemoved = 0;
  struct Node* prevHead = NULL;
  struct Node* tempHead = list->head;
  while(list->head != NULL)
    {
      if(list->head->data == dataToRemove && list->head->dataSize == numElements)
	{
	  if(tempHead == list->head)
	    {
	      list->head = list->head->next;
	      destroyNode(tempHead);
	      prevHead = NULL;
	      tempHead = list->head;
	      elementsRemoved++;
	    }
	  else
	    {
	      prevHead->next = list->head->next;
	      destroyNode(list->head);
	      list->head = prevHead;
	      elementsRemoved++;
	    }
	}
      if(prevHead)
	{
	  prevHead = list->head;
	  list->head = list->head->next;  
	}
      else
	{
	  prevHead = list->head;
	}
    }
  
  list->head = tempHead;
  return elementsRemoved;
}

int insert(struct ListFile* list, char* nameToAdd, void* dataToAdd, int numElements)
{
  //If the list starts out empty
  if(list->head == NULL)
    {
      struct Node* newNode = constructNode(nameToAdd, dataToAdd, numElements);
      list->head = newNode;
      return 1;
    }
  //Inserting into the middle of the list
  struct Node* tempHead = list->head;
  struct Node* prevNode = NULL;
  while(list->head != NULL)
    {
      if(strcmp(list->head->name, nameToAdd) < 0)
	{
	  prevNode = list->head;
	  list->head = list->head->next;
	}
      else if(strcmp(list->head->name, nameToAdd) > 0)
	{
	  struct Node* newNode = constructNode(nameToAdd, dataToAdd, numElements);
	  newNode->next = list->head;

	  if(prevNode)
	    {
	      prevNode->next = newNode;
	      list->head = tempHead;
	    }
	  else
	    {
	      list->head = newNode;
	    }
	  return 1;
	}
      else
	{
	  return 0;
	}
    }
  //Inserting at the end of the list
  if(list->head == NULL)
    {
      struct Node* newNode = constructNode(nameToAdd, dataToAdd, numElements);
      prevNode->next = newNode;
      list->head = tempHead;
      return 1;
    }
  return 0;
}

struct ListFile* readFile(char* fileName)
{
  struct ListFile* newList = makeList();
  FILE* fileToRead = fopen(fileName, "r");
  if(!fileToRead)
    {
      return NULL;
    }
  char* word = NULL;
  while(fscanf(fileToRead, "%ms", &word) != EOF)
    {
      insert(newList, word, word, strlen(word));
      free(word);
      word = NULL;
    }
  fclose(fileToRead);
  return newList;
}

int appendFromFile(struct ListFile* list, char* fileName)
{
  int elementsAdded = 0;
  FILE* fileToAppend = fopen(fileName, "r");
  if(!fileToAppend)
    {
      return -1;
    }
  char* word = NULL;
  struct Node *tempHead = list->head;
  struct Node *prevHead = NULL;
  while(list->head != NULL)
    {
      prevHead = list->head;
      list->head = list->head->next;
    }
  while(fscanf(fileToAppend, "%ms", &word) != EOF)
    {
      list->head = constructNode(word, word, strlen(word));
      prevHead->next = list->head;
      elementsAdded++;
      free(word);
      word = NULL;
      prevHead = list->head;
      list->head = list->head->next;
    }
  fclose(fileToAppend);
  list->head = tempHead;
  return elementsAdded;
}

int saveToFile(struct ListFile* list, char* fileName)
{
  struct Node* tempHead = list->head;
  FILE* fileToSave = fopen(fileName, "w+");
  if(!fileToSave)
    {
      return -1;
    }
  while(list->head != NULL)
    {
      fprintf(fileToSave, "%s ", list->head->name);
      list->head = list->head->next;
    }
  fclose(fileToSave);
  list->head = tempHead;
  return 0;
}

void* getElement(struct ListFile* list, int index)
{
  int indexCheck = 0;
  if(indexCheck > index)
    {
      return NULL;
    }
  struct Node* tempHead = list->head;
  while(tempHead != NULL)
    {
      if(indexCheck == index)
	{
	  return tempHead->data;
	}
      tempHead = tempHead->next;
      indexCheck++;
    }
  return NULL;
}

char* getElementName(struct ListFile* list, int index)
{
  int indexCheck = 0;
  if(indexCheck > index)
    {
      return NULL;
    }
  struct Node* tempHead = list->head;
  while(tempHead != NULL)
    {
      if(indexCheck == index)
	{
	  return tempHead->name;
	}
      tempHead = tempHead->next;
      indexCheck++;
    }
  return NULL;
}

char* toString(struct ListFile* list)
{
  char *retval = (char *)malloc(100 * sizeof(char));
  struct Node* tempHead = list->head;
  int idx = 0;
  while(list->head != NULL)
    {
      if(strlen(retval) + strlen(list->head->name) > 100)
	{
	  char *temp = (char *)malloc(strlen(retval)*2 * sizeof(char));
	  for(int i = 0; i < strlen(retval)+1; i++)
	    {
	      temp[i] = retval[i];
	    }
	  free(retval);
	  retval = temp;
	  temp = NULL;
	}
      for(int i  = 0; i < strlen(list->head->name); i++)
	{
	  //idx++;
	  retval[idx] = list->head->name[i];
	  idx++;
	}
      idx--;
      list->head = list->head->next;
      if(list->head != NULL)
	{
	  idx++;
	  retval[idx] = '-';
	  idx++;
	  retval[idx] = '>';
	  idx++;
	}
    }
  idx++;
  retval[idx] = '\0';
  list->head = tempHead;
  return retval;
}
 
#endif
