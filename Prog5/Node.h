/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Single Linked List
  Program #5
*/

#ifndef NODE_H
#define NODE_H

struct Node
{
  struct Node *next;
  char *name;
  void *data;
  int dataSize;
};

struct Node* constructNode(char*, void*, int);
struct Node* destroyNode(struct Node*);
//char* toString();
#endif
