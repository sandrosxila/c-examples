#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct Stack Stack;

Stack *new_stack();
void push(Stack *s, int element);
int size(Stack *s);
int top(Stack *s);
bool empty(Stack *s);
int pop(Stack *s);
void delete_stack(Stack *s);

#endif // STACK_H
