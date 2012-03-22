#ifndef HEAP_H
#define HEAP_H
#include "config.h"

typedef struct RAM_CELL
{
	ramword_t value;
  struct ramaddr_t* next;
  struct ramaddr_t* previous;
} ramaddr_t;

ramaddr_t* heap_init(size_t heapsize);
void heap_add(ramaddr_t* heap);
ramaddr_t* heap_leap(ramaddr_t* start,int jump_size);
int heap_load(ramaddr_t* heap,ramword_t* data,size_t n);
void heap_free(ramaddr_t* heap);

#endif
