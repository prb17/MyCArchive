/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  <Memory Allocater>
  Program #4
*/

#ifndef ALLOC_C
#define ALLOC_C
#include"Alloc.h"
#include<stdlib.h>
#include<stdio.h>

struct Alloc* constructAlloc(size_t size)
{
  if (size < 0)
    {
      return NULL;
    }
  struct Alloc *memChunk = (struct Alloc *)malloc(sizeof(struct Alloc));
  if(size % 16 != 0) //round number to multiple of 16 if it isnt already
    {
      size += (16 - (size % 16));
    }
  memChunk->memory = (void *)malloc(size * sizeof(void));
  memChunk->memoryInUse = (void **)malloc(size * sizeof(void));
  memChunk->memoryInUseSize = (size_t *)malloc(size * sizeof(size_t));
  memChunk->memoryEnd = memChunk->memory + size;
  memChunk->capacity = size;
  memChunk->size = 0;
  memChunk->numAllocs = 0;
  memChunk->test = (char *)memChunk;
  return memChunk;
}

struct Alloc* destroyAlloc(struct Alloc* memChunk)
{
  free(memChunk->memory);
  free(memChunk->memoryInUseSize);
  free(memChunk->memoryInUse);
  free(memChunk);
  return NULL;
}

void *allocate(struct Alloc* memChunk, size_t size)
{
  if (memChunk == NULL)
    {
      return NULL;
    }
  if(size % 16 != 0) //round number to multiple of 16 if it isnt
			//already
    {
      size += (16 - (size % 16));
    }
  
  if(memChunk->memoryEnd - memChunk->memory >= size) //if there is enough room in the allocated
    //memory to fulfil request
    {	 
      memChunk->memoryEnd -= size;
      memChunk->memoryInUse[memChunk->numAllocs] = memChunk->memoryEnd;
      memChunk->memoryInUseSize[memChunk->numAllocs] = size;
      memChunk->size += size;
      memChunk->numAllocs++;
      return memChunk->memoryEnd;
    }
  else
    {
      return NULL;
    }
}

void deallocate(struct Alloc* memChunk, void *ptr)
{
  if(ptr == NULL)
    {
      fprintf(stderr, "corruption in free\n");
      exit(2);
    }
  else
    {
      for(int i = 0; i < memChunk->capacity; i++)
	{
	  if (ptr == memChunk->memoryInUse[i])
	    {
	      memChunk->memoryEnd += (size_t)memChunk->memoryInUseSize[i];
	      memChunk->size -= memChunk->memoryInUseSize[i];
	      memChunk->memoryInUseSize[i] = 0;
	      memChunk->memoryInUse[i] = 0;
	      memChunk->numAllocs--;
	      break;
	    }
	  if (i == memChunk->capacity - 1)
	    {
	      fprintf(stderr, "corruption in free\n");
	      exit(2);
	    }
	}
    }
}

size_t getCapacity(struct Alloc* memChunk)
{
  return memChunk->capacity;
}

size_t getSize(struct Alloc* memChunk)
{
  return memChunk->size;
}

void* getBase(struct Alloc* memChunk)
{
  return memChunk->memory;
}

size_t getNumAllocations(struct Alloc* memChunk)

{
  return memChunk->numAllocs;
}

void** getAllocations(struct Alloc* memChunk)
{
  return memChunk->memoryInUse;
}

int needDeallocate(struct Alloc* memChunk)
{
  if(getAllocations(memChunk) != NULL)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

void *riskyAlloc(struct Alloc* memChunk, size_t size)
{
  if(size % 16 != 0) //round number to multiple of 16 if it isnt
    //already
    {
      size += (16 - (size % 16));
    }
  if(memChunk->size > size)
    {
      return allocate(memChunk, size);
    }
  else
    {
      size += size - memChunk->size;
      memChunk->memory = (void *)realloc(memChunk->memory, size);
    }
  if (memChunk->memory == NULL)
    {
      fprintf(stderr, "Bad realloc\n");
      exit(3);
      return NULL;
    }
  memChunk->capacity = size;
  return memChunk->memory;
  }

#endif
