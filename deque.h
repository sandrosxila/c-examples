#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>

typedef struct Deque Deque;

Deque *deque_create();
void deque_push_back(Deque *d, int value);
void deque_push_front(Deque *d, int value);
int deque_pop_back(Deque *d);
int deque_pop_front(Deque *d);
int deque_front(Deque *d);
int deque_back(Deque *d);
int deque_size(Deque *d);
bool deque_empty(Deque *d);
void deque_destroy(Deque *d);

#endif // !DEQUE_H