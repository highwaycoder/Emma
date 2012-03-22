#ifndef STACK_H
#define STACK_H

typedef struct NODE {
  int value;
  struct node_t* down;
} node_t;

typedef struct STACK {
  struct node_t* top;
  unsigned int size;
  unsigned int max_size;
  int overflow;
} stack_t;

stack_t* st_create(size_t max_size);
int st_pop(stack_t* from);
void st_push(stack_t* to,int value);
void st_free(stack_t* stack);

#endif
