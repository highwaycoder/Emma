#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "emu8086.h" 
#include "heap.h"

// create a new heap with the size given
ramaddr_t* heap_init(size_t heapsize)
{
  ramaddr_t* rv = malloc(sizeof(ramaddr_t));
  int i=0;
  ramaddr_t* top = rv;
  while(i < heapsize)
  {
    heap_add(rv);
    rv->value = 0xDEAD; // initial ram value should be something we can easily recognise
    // move the list right after adding
    rv = (ramaddr_t*)rv->next;
    i++;
  }
  rv = top; // fast-rewind the list before returning it
  return rv;
}

// add a single element to the heap (just a helper function for heap_init)
void heap_add(ramaddr_t* heap)
{
  // this just makes sure we're not trying to call heap->next on a null pointer
  // in actuality, that is an impossible case, but programmers
  // are programmers.
  if(heap==NULL) heap = heap_init(0);
  if(heap->next==NULL)
  {
    heap->next = malloc(sizeof(ramaddr_t));
    memset(heap->next,0,sizeof(ramaddr_t));
  }
}

// relative jump
ramaddr_t* heap_leap(ramaddr_t* start,int jump_size)
{
  if(jump_size < 0)
  {
    while(jump_size < 0)
    {
      start = (ramaddr_t*)start->previous;
      jump_size++;
    }
  }
  else
  {
    while(jump_size > 0)
    {
      start = (ramaddr_t*)start->next;
      jump_size--;
    }
  }
  return start;
}

int heap_load(ramaddr_t* heap,ramword_t* data,size_t n)
{
  int i=0;
  if(HEAPSIZE < n)
  {
    printf("HEAPSIZE < n\n");
    return 0;
  }
  while(i<n)
  {
    heap->value = data[i];
    heap = (ramaddr_t*)heap->next;
    if(heap==NULL)
    {
      fprintf(stderr,"how the feck did this happen?!");
      return 0;
    }
    i++;
  }
  return 1;
}

void heap_free(ramaddr_t* heap)
{
  ramaddr_t* tmp;
  // if heap is null, our job has already been done for us
  if(heap==NULL) return;
  // rewind heap so we definitely catch all the memory
  while(heap->previous!=NULL) heap = (ramaddr_t*)heap->previous;
  // free the memory one cell at a time
  while(heap!=NULL)
  {
    tmp = heap;
    heap = (ramaddr_t*)heap->next;
    free(tmp);
  }
}
