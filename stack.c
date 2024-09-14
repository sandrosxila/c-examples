#include "vector.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct Vector Stack;

Stack *new_stack()
{
  Stack* s = new_vector();
  return s;
}

int pop(Stack* s){
  return pop_back(s);
}

void push(Stack* s, int element){
  append(s, element);
}

bool empty(Stack* s) {
  return len(s) == 0;
}

int size(Stack *s){
  return len(s);
}

int top(Stack* s){
  return back(s);
}

void delete_stack(Stack* s) {
  delete_vector(s);
}