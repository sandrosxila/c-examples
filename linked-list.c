#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node *head;
    int size;
} List;

static Node* create_node(int value) {
    // allocating new node on heap
    Node *newNode = (Node*)malloc(sizeof(Node));

    // if compiler fails to allocate the memory block
    if(newNode == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE); // terminate the program
    }

    // set node value
    newNode->value = value;

    // next node points to nowhere
    newNode->next = NULL;

    return newNode;
}

static void add_item(Node* head, int value) {
    Node *last = head; // declare the last element as first

    // searching for the last element
    while(last->next != NULL) {
        last = last->next;
    }

    // adding a new node as a last element
    last->next = create_node(value);
}

static Node *get_item(Node* head, int pos) {
    for(Node* current = head; current != NULL && pos >= 0; current = current->next, pos--){
        if(pos == 0){
            return current;
        }
    };

    return NULL;
}

static bool delete_item(Node** head, int value) {
    Node *previous = NULL, *current;

    // locating the current and previous node
    for (current = *head; current != NULL; previous = current, current = current->next) {
        if(current->value == value) {
            break;
        }
    }

    if(current == NULL){
        return false;
    }

    if(previous == NULL) 
        *head = (*head)->next; // edit original head node
    else 
        previous->next = current->next; // tie adjacent nodes
    
    // delete the current node
    free(current);

    return true;
}

List *list_create() {
    List *list = malloc(sizeof(List));

    if(list == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE); // terminate the program
    }

    list->head = NULL;
    list->size = 0;

    return list;
}

void list_push(List* list, int value) {
    if(!list->head) {
        list->head = create_node(value);
    } else{
        add_item(list->head, value);
    }

    list->size++;
}

Node *list_at(List* list, int index) {
    return get_item(list->head, index);
}

void list_erase(List* list, int value) {
    if(delete_item(&list->head, value)) {
        list->size--;
    }
}

void list_clear(List* list) {
    for(Node *current = list->head, *nextNode; current != NULL; current = nextNode){
        nextNode = current->next;
        free(current);
    }

    list->head = NULL;
    list->size = 0;
}

int list_size(List *list) {
    return list->size;
}

bool list_empty(List *list) {
    return list->size == 0;
}