#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct Stack Stack;

Stack *stack_create();
void stack_push(Stack *s, int element);
int stack_size(Stack *s);
int stack_top(Stack *s);
bool stack_empty(Stack *s);
int stack_pop(Stack *s);
void stack_destroy(Stack *s);

#endif // STACK_H
