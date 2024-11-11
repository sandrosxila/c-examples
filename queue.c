#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int start;
  int end;
  Vector* v;
} Queue;

Queue *queue_create()
{
  Queue* q = malloc(sizeof(Queue));
  if(q == NULL) {
    printf("Error: malloc failed to allocate space the queue %p\n", &q);
    exit(EXIT_FAILURE);
  }

  q->v = vector_create();
  q->start = 0;
  q->end = 0;

  return q;
}

int queue_pop(Queue* q){
  return vector_at(q->v, q->start++);
}

static void queue_shift(Queue* q) {
  int diff = q->start;
  int n = vector_size(q->v);

  for(int i = 0; i < n - diff; i++){
    vector_set(q->v, i, vector_at(q->v, i + diff));
  }

  q->end -= diff;
}

void queue_push(Queue* q, int element){
  if(q->end + 1 > vector_capacity(q->v) && q->start > 0) {
    queue_shift(q);
  }

  if(q->end + 1 < vector_size(q->v)) {
    vector_set(q->v, q->end + 1, element);
  }
  else {
    vector_push_back(q->v, element);
  }

  q->end++;
}

bool queue_empty(Queue* q) {
  return vector_size(q->v) - q->start == 0;
}

int queue_size(Queue *q){
  return vector_size(q->v) - q->start;
}

int queue_front(Queue* q){
  return vector_at(q->v, q->start);
}

void queue_delete(Queue* q) {
  vector_destroy(q->v);
  free(q);
  q = NULL;
}