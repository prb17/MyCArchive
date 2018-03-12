/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Single Linked List
  Program #5
 */

#ifndef LISTFILE_H
#define LISTFILE_H

#include"Node.h"

struct ListFile
{
  struct Node* head;
};

struct ListFile* makeList();
struct ListFile* copyList(struct ListFile*);
struct ListFile* destroyList(struct ListFile*);
void* findByName(struct ListFile*, char*);
int findByData(struct ListFile*, void*, int);
int removeByName(struct ListFile*, char*);
int removeByData(struct ListFile*, void*, int);
int insert(struct ListFile*, char*, void*, int);
struct ListFile* readFile(char*);
int appendFromFile(struct ListFile*, char*);
int saveToFile(struct ListFile*, char*);
void* getElement(struct ListFile*, int);
char* getElementName(struct ListFile*, int);
char* toString(struct ListFile*);
#endif
