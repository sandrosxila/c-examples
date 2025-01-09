#ifndef BST_H

typedef struct BST BST;

BST *bst_create();

void bst_insert(BST *bst, int value);

void bst_erase(BST *bst, int value);

int bst_at(BST *bst, int index);

int bst_size(BST *bst);

void bst_balance(BST* bst);

void bst_destroy(BST* bst);

#endif // !BST_H
