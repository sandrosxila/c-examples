#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct List List;

List *list_create();

void list_push(List* list, int value);

Node *list_at(List* list, int index);

void list_erase(List* list, int value);

void list_clear(List* list);

int list_size(List* list);

bool list_empty(List* list);

#endif // LINKED_LIST_H