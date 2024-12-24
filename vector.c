#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
  int capacity;
  int size;
  int *buffer;
} Vector;

Vector *vector_create()
{
  Vector *v = (Vector *)malloc(sizeof(Vector));

  if (v == NULL)
  {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE); // terminate the program
  }

  v->size = 0;
  v->capacity = 1;
  v->buffer = (int *)malloc(v->capacity * sizeof(int));

  if (v->buffer == NULL)
  {
    fprintf(stderr, "Error: malloc failed to allocate space the vector %p\n", &v);
    exit(EXIT_FAILURE);
  }

  return v;
}

void vector_push_back(Vector *v, int element)
{
  if (v->size + 1 > v->capacity)
  {
    v->buffer = (int *)realloc(v->buffer, 2 * v->capacity * sizeof(int));

    if (v->buffer == NULL)
    {
      fprintf(stderr, "Error: malloc failed to allocate space the vector %p\n", &v);
      exit(EXIT_FAILURE);
    }
    v->capacity *= 2;
  }

  v->buffer[v->size++] = element;
}

int vector_pop_back(Vector *v) {
  if (v->size == 0) {
    fprintf(stderr, "vector is empty");
    exit(EXIT_FAILURE);
  }

  return v->buffer[--v->size];
}

int vector_at(Vector *v, int index)
{
  if (index >= v->size)
  {
    fprintf(stderr, "index is out of bounds");

    exit(EXIT_FAILURE);
  }

  return v->buffer[index];
}

int vector_set(Vector *v, int index, int value)
{
  if (index >= v->size)
  {
    fprintf(stderr, "index is out of bounds");

    exit(EXIT_FAILURE);
  }

  return v->buffer[index] = value;
}

bool vector_empty(Vector *v)
{
  return v->size == 0;
}

int vector_capacity(Vector *v)
{
  return v->capacity;
}

int vector_size(Vector *v)
{
  return v->size;
}

int vector_back(Vector *v)
{
  return v->buffer[v->size - 1];
}

void vector_clear(Vector *v)
{
  v->size = 0;
  v->capacity = 1;

  free(v->buffer);

  v->buffer = (int *)malloc(v->capacity * sizeof(int));

  if (v->buffer == NULL)
  {
    fprintf(stderr, "Error: malloc failed to allocate space the vector %p\n", &v);
    exit(EXIT_FAILURE);
  }
}

void vector_destroy(Vector *v)
{
  free(v->buffer);
  free(v);

  v = NULL;
}