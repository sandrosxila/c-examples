#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int max(int a, int b) { return a > b ? a : b; }

typedef struct Node {
    int value;
    int height;
    struct Node* right;
    struct Node* left;
} Node;

typedef struct {
    Node *root;
    int size;
} AVL;

Node *node_create(int value) {
    Node *node = malloc(sizeof(Node));
    if(node == NULL) {
        fprintf(stderr, "Memory Allocation failed for AVL Node.\n");
        exit(EXIT_FAILURE); // terminate the program
    }
    
    node->value = value;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}

AVL *avl_create() {
    AVL *avl = malloc(sizeof(AVL));
    if(avl == NULL) {
        fprintf(stderr, "Memory Allocation failed for AVL.\n");
        exit(EXIT_FAILURE); // terminate the program
    }
    
    avl->root = NULL;
    avl->size = 0;

    return avl;
}

static int node_height(Node *node) { return node == NULL ? -1 : node->height; }

static Node *right_rotate(Node *z) {
    Node *y = z->left;

    z->left = y->right;
    y->right = z;

    z->height = 1 + max(node_height(z->left), node_height(z->right));
    y->height = 1 + max(node_height(y->left), node_height(y->right));

    return y;
}

static Node *left_rotate(Node *z) {
    Node *y = z->right;

    z->right = y->left;
    y->left = z;

    z->height = 1 + max(node_height(z->left), node_height(z->right));
    y->height = 1 + max(node_height(y->left), node_height(y->right));

    return y;
}

static Node *node_insert(Node *current, int value) {
    if(current == NULL)
        return node_create(value);

    if(value < current->value) {
        current->left = node_insert(current->left, value);
    }
    else {
        current->right = node_insert(current->right, value);
    }

    current->height = 1 + max(node_height(current->left), node_height(current->right));

    int balance_factor = node_height(current->left) - node_height(current->right);

    // Left Left Case
    if(balance_factor > 1 && value < current->left->value){
        return right_rotate(current);
    }
    // Right Right Case
    if(balance_factor < -1 && value >= current->right->value) {
        return left_rotate(current);
    }
    // Left Right Case
    if(balance_factor > 1 && value >= current->left->value){
        current->left = left_rotate(current->left);
        return right_rotate(current);
    }
    // Right Left Case
    if(balance_factor < -1 && value < current->right->value) {
        current->right = right_rotate(current->right);
        return left_rotate(current);
    }

    return current;
}

void avl_insert(AVL* avl, int value) {
    avl->root = node_insert(avl->root, value);
    avl->size++;
}