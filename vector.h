#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef struct Vector Vector;

Vector *new_vector();
void append(Vector *v, int element);
int len(Vector *v);
int back(Vector *v);
bool empty(Vector *v);
int pop_back(Vector *v);
int get(Vector *v, int index);
int set(Vector *v, int index, int value);
void delete_vector(Vector *v);

#endif // VECTOR_H
