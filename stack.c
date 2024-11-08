#include "vector.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct Vector Stack;

Stack *stack_create()
{
  Stack *s = vector_create();
  return s;
}

int stack_pop(Stack *s)
{
  return vector_pop_back(s);
}

void stack_push(Stack *s, int element)
{
  vector_append(s, element);
}

bool stack_empty(Stack *s)
{
  return vector_empty();
}

int stack_size(Stack *s)
{
  return vector_size(s);
}

int stack_top(Stack *s)
{
  return vector_back(s);
}

void stack_clear(Stack *s)
{
  vector_clear(s);
}

void stack_destroy(Stack *s)
{
  vector_destroy(s);
}