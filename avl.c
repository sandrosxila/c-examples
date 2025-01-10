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
static int node_balance_factor(Node *node) { return node_height(node->left) - node_height(node->right); }

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

static Node *rebalance(Node *current) {
    int balance_factor = node_balance_factor(current);

    // Left Left Case
    if(balance_factor > 1 && node_balance_factor(current->left) >= 0){
        return right_rotate(current);
    }
    // Right Right Case
    if(balance_factor < -1 && node_balance_factor(current->right) <= 0) {
        return left_rotate(current);
    }
    // Left Right Case
    if(balance_factor > 1 && node_balance_factor(current->left) == -1){
        current->left = left_rotate(current->left);
        return right_rotate(current);
    }
    // Right Left Case
    if(balance_factor < -1 && node_balance_factor(current->right) == 1) {
        current->right = right_rotate(current->right);
        return left_rotate(current);
    }

    return current;
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

    return rebalance(current);
}

void avl_insert(AVL* avl, int value) {
    avl->root = node_insert(avl->root, value);
    avl->size++;
}

static Node *node_erase(Node *current, int value, int *size){
    if(value < current->value) {
        current->left = node_erase(current->left, value, size);
    }
    else if (value > current->value) {
        current->right = node_erase(current->right, value, size);
    }
    else {
        // CASE 1: LEAF NODE
        if(current->left == NULL && current->right == NULL){
            free(current);
            (*size)--;
            return NULL;
        }
        // CASE 2: NODE WITH ONE CHILD
        else if(current->left == NULL || current->right == NULL){
            Node *child = current->left != NULL ? current->left : current->right;
            free(current);
            (*size)--;
            return child;
        }
        // CASE 3: NODE WITH TWO CHILDREN
        else {
            Node *next = current->right;
            while(next->left != NULL){
                next = next->left;
            }

            current->value = next->value;
            current->right = node_erase(current->right, next->value, size);
        }
    }

    current->height = 1 + max(node_height(current->left), node_height(current->right));

    return rebalance(current);
}

void avl_erase(AVL* avl, int value){
    avl->root = node_erase(avl->root, value, &(avl->size));
}


static void node_at(Node* current, int index, int *pos, int *res) {
    if(current == NULL)
        return;

    node_at(current->left, index, pos, res); 
    if(((*pos)++) == index) {
        *res = current->value;
        return;
    }

    node_at(current->right, index, pos, res);
}

int avl_at(AVL *avl, int index) {
    int pos = 0, res = 0;
    node_at(avl->root, index, &pos, &res);
    return res;
}

int avl_size(AVL *avl) {
    return avl->size;
}

static void node_destroy(Node *current) {
    if(current == NULL)
        return;

    node_destroy(current->left);
    node_destroy(current->right); 
    free(current);
}

void avl_destroy(AVL* avl) {
    node_destroy(avl->root);
    free(avl);
}
