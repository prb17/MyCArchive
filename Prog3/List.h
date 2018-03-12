/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Structing items in a List
  Program #3
 */

#ifndef LIST_H
#define LIST_H
#include<stdlib.h>

struct Node
{
  int value;
  struct Node* nextNode;
} Node;

struct Node* constructList(int);
struct Node* destroyList(struct Node*);
struct Node* insert(struct Node*, int);
struct Node* removeItem(struct Node*, int);
int traverse(struct Node*, char *);
int find(struct Node*, int);
char* traverse2(struct Node*);
size_t size(struct Node*);

#endif
