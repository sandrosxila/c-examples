#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
  int capacity;
  int size;
  int *buffer;
} Vector;

Vector *new_vector()
{
  Vector *v = (Vector *)malloc(sizeof(Vector));
  v->size = 0;
  v->capacity = 1;
  v->buffer = (int *)malloc(v->capacity * sizeof(int));
  return v;
}

void append(Vector *v, int element)
{
  if (v->size + 1 > v->capacity)
  {
    v->buffer = (int *)realloc(v->buffer, 2 * v->capacity * sizeof(int));
    v->capacity *= 2;
  }

  v->buffer[v->size++] = element;
}

int pop_back(Vector *v)
{
  return v->buffer[--v->size];
}

int get(Vector *v, int index)
{
  return v->buffer[index];
}

int set(Vector *v, int index, int value)
{
  return v->buffer[index] = value;
}

bool is_empty(Vector *v) {
  return v->size == 0;
}

int len(Vector *v) {
  return v->size;
}

int back(Vector *v){
  return v->buffer[v->size - 1];
}

void delete_vector(Vector *v) {
  free(v->buffer);
  free(v);
}