#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef struct Vector Vector;

Vector *vector_create();
void vector_push_back(Vector *v, int element);
int vector_capacity(Vector *v);
int vector_size(Vector *v);
int vector_back(Vector *v);
bool vector_empty(Vector *v);
int vector_pop_back(Vector *v);
int vector_at(Vector *v, int index);
int vector_set(Vector *v, int index, int value);
void vector_destroy(Vector *v);

#endif // VECTOR_H
