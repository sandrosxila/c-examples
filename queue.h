#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct Queue Queue;

Queue *queue_create();
void queue_push(Queue *q, int element);
int queue_size(Queue *q);
int queue_front(Queue *q);
int queue_back(Queue *q);
bool queue_empty(Queue *q);
int queue_pop(Queue *q);
void queue_clear(Queue *q);
void queue_destroy(Queue *q);

#endif // QUEUE_H
