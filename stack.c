#include <stdlib.h>
#include <string.h>
#include "stack.h"

// create a new stack
stack_t* st_create(size_t max_size)
{
  stack_t* rv = malloc(sizeof(stack_t));
  memset(rv,0,sizeof(stack_t));
  rv->max_size = max_size;
  return rv;
}

// pop a node off the stack
int st_pop(stack_t* from)
{
  int rv;
  struct node_t* to_free;
  if(from->top == NULL) 
  {
    from->overflow--;
    // return how many pops we've done that are too many pops
    return from->overflow;
  }
  rv = ((node_t*)from->top)->value;
  to_free = from->top;
  from->top = ((node_t*)from->top)->down;
  free(to_free);
  return rv;
}

// push a node to the stack
void st_push(stack_t* to,int value)
{
  struct node_t* new_node;
  if(to->size >= to->max_size-1)
  {
    to->overflow++;
    return; // otherwise our stack would be bugged
  }
  
  new_node = malloc(sizeof(node_t));
  ((node_t*)new_node)->value = value;
  ((node_t*)new_node)->down = to->top;
  to->top = new_node;
}

// free a whole stack at once
void st_free(stack_t* stack)
{
  struct node_t* top = stack->top;
  while(top!=NULL) {
    stack->top = ((node_t*)top)->down;
    free(top);
    top = stack->top;
  }
  free(stack); // finally, free the actual stack pointer
}
