#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *prev;
  struct Node *next;
} Node;

Node *node_create(int value, Node *prev, Node *next) {
  Node *node = (Node *)malloc(sizeof(Node));

  if (node == NULL)
  {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE); // terminate the program
  }

  node->value = value;
  node->prev = prev;
  node->next = next;

  return node;
}

typedef struct {
  Node* head;
  Node* tail;
  int size;
} Deque;

Deque *deque_create() {
  Deque *d = (Deque *)malloc(sizeof(Deque));

  if (d == NULL)
  {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE); // terminate the program
  }

  d->head = NULL;
  d->tail = NULL;
  d->size = 0;

  return d;
}

void deque_push_back(Deque *d, int value) {
  if(d->tail == NULL){
    d->tail = node_create(value, NULL, NULL);
    d->head = d->tail;
  }
  else {
    d->tail->next = node_create(value, d->tail, NULL);
    d->tail = d->tail->next;
  }

  d->size++;
}

void deque_push_front(Deque *d, int value) {
  if(d->head == NULL){
    d->head = node_create(value, NULL, NULL);
    d->tail = d->head;
  }
  else {
    d->head->prev = node_create(value, NULL, d->head);
    d->head = d->head->prev;
  }

  d->size++;
}

int deque_pop_back(Deque *d) {
  if (d->tail == NULL) {
    fprintf(stderr, "Deque is empty\n");
    exit(EXIT_FAILURE); // terminate the program
  }

  int value = d->tail->value;

  if(d->tail->prev == NULL) {
    free(d->tail);
    d->tail = NULL;
    d->head = NULL;
  }
  else {
    d->tail = d->tail->prev;
    free(d->tail->next);
    d->tail->next = NULL;
  }

  d->size--;

  return value;
}

int deque_pop_front(Deque *d) {
  if (d->head == NULL) {
    fprintf(stderr, "Deque is empty\n");
    exit(EXIT_FAILURE); // terminate the program
  }

  int value = d->head->value;

  if(d->head->next == NULL) {
    free(d->head);
    d->head = NULL;
    d->tail = NULL;
  }
  else {
    d->head = d->head->next;
    free(d->head->prev);
    d->head->prev = NULL;
  }

  d->size--;

  return value;
}

int deque_front(Deque *d) {
  if (d->head == NULL) {
    fprintf(stderr, "Deque is empty\n");
    exit(EXIT_FAILURE); // terminate the program
  }

  return d->head->value;
}

int deque_back(Deque *d) {
  if (d->tail == NULL) {
    fprintf(stderr, "Deque is empty\n");
    exit(EXIT_FAILURE); // terminate the program
  }

  return d->tail->value;
}

int deque_size(Deque *d) {
  return d->size;
}

bool deque_empty(Deque *d) {
  return d->size == 0;
}

void deque_destroy(Deque *d) {
  for(Node* curr = d->head, *nextNode = NULL; curr != NULL; curr = nextNode) {
    nextNode = curr->next;
    free(curr);
  }

  free(d);

  d = NULL;
}