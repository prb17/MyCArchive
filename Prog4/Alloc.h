/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  <Program Description>
  Program #4
*/

#ifndef ALLOC_H
#define ALLOC_H
#include<stdlib.h>

struct Alloc
{
  void *memory;
  void *memoryEnd;
  void **memoryInUse;
  size_t *memoryInUseSize;
  size_t capacity;
  size_t size;
  size_t numAllocs;
  char *test;
};

struct Alloc* contstructAlloc(size_t);
struct Alloc* destroyAlloc(struct Alloc*);
void *allocate(struct Alloc*, size_t);
void deallocate(struct Alloc*, void*);
size_t getCapacity(struct Alloc*);
size_t getSize(struct Alloc*);
void* getBase(struct Alloc*);
size_t getNumAllocations(struct Alloc*);
void** getAllocations(struct Alloc*);
int needDeallocate(struct Alloc*);
void *riskyAlloc(struct Alloc*, size_t);

#endif
