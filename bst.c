#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node* right;
    struct Node* left;
} Node;

typedef struct {
    Node *root;
    int size;
} BST;

Node *node_create(int value) {
    Node *node = malloc(sizeof(Node));
    if(node == NULL) {
        fprintf(stderr, "Memory Allocation failed for BST Node.\n");
        exit(EXIT_FAILURE); // terminate the program
    }
    
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

BST *bst_create() {
    BST *bst = malloc(sizeof(BST));
    if(bst == NULL) {
        fprintf(stderr, "Memory Allocation failed for BST.\n");
        exit(EXIT_FAILURE); // terminate the program
    }
    
    bst->root = NULL;
    bst->size = 0;

    return bst;
}

static void node_insert(Node *current, int value) {
    if(value < current->value) {
        if(current->left == NULL){
            current->left = node_create(value);
        }
        else {
            node_insert(current->left, value);
        }
    }
    else {
        if(current->right == NULL){
            current->right = node_create(value);
        }
        else {
            node_insert(current->right, value);
        }
    }
}

void bst_insert(BST *bst, int value) {
    if(bst->root == NULL)
        bst->root = node_create(value);
    else
        node_insert(bst->root, value);
    bst->size++;
}

static bool node_erase(Node* parent, Node *current, int value){
    if(current == NULL){
        return false;
    }

    if(value < current->value) {
        return node_erase(current, current->left, value);
    }
    else if (value > current->value) {
        return node_erase(current, current->right, value);
    }
    else {
        // CASE 1: LEAF NODE
        if(current->left == NULL && current->right == NULL){
            if(parent->value > current->value){
                free(parent->left);
                parent->left = NULL;
                return true;
            }
            else {
                free(parent->right);
                parent->right = NULL;
                return true;
            }
        }
        // CASE 2: NODE WITH ONE CHILD
        else if(current->left == NULL || current->right == NULL){
            if(parent->value > current->value){
                parent->left = current->left == NULL ? current->right : current->left;
            }
            else {
                parent->right = current->left == NULL ? current->right : current->left;
            }

            free(current);
            return true;
        }
        // CASE 3: NODE WITH TWO CHILDREN
        else {
            Node *next = current->right, *nextParent = current;
            while(next->left != NULL){
                nextParent = next;
                next = next->left;
            }

            current->value = next->value;
            return node_erase(nextParent, next, next->value);
        }
    }

    return false;
}

void bst_erase(BST *bst, int value) {
    Node sentinel = {.value = INT_MIN, .left = NULL, .right = bst->root};
    if(node_erase(&sentinel, bst->root, value)) {
        bst->size--;
    };
    bst->root = sentinel.right;
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

int bst_at(BST *bst, int index) {
    int pos = 0, res = 0;
    node_at(bst->root, index, &pos, &res);
    return res;
}

int bst_size(BST *bst) {
    return bst->size;
}

static void node_fill_array(Node *arr[], int *pos, Node **current) {
    if(*current == NULL)
        return;

    node_fill_array(arr, pos, &((*current)->left));
    arr[(*pos)++] = *current;
    node_fill_array(arr, pos, &((*current)->right));
}

static void node_balance(Node *arr[], int l, int r, Node *current) {
    if(current == NULL){
        return;
    }

    int mid = (l + r) / 2;
    current->left = arr[(l + mid) / 2];
    arr[(l + mid) / 2] = NULL;
    current->right = arr[((mid + 1) + r) / 2];
    arr[((mid + 1) + r) / 2] = NULL;

    node_balance(arr, l, mid, current->left);
    node_balance(arr, mid + 1, r, current->right);
}

void bst_balance(BST* bst) {
    Node* sorted[bst->size];
    int pos = 0, mid = (bst->size - 1) / 2;
    node_fill_array(sorted, &pos, &bst->root);
    for(int i = 0; i < pos; i++) {
        sorted[i]->left = NULL;
        sorted[i]->right = NULL;
    }

    bst->root = sorted[mid];
    sorted[mid] = NULL;
    node_balance(sorted, 0, bst->size - 1, bst->root);
}

static void node_destroy(Node *current) {
    if(current == NULL)
        return;
    node_destroy(current->left);
    node_destroy(current->right); 
    free(current);
}

void bst_destroy(BST* bst) {
    node_destroy(bst->root);
    free(bst);
}
