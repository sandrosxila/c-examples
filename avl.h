#ifndef AVL_H

typedef struct AVL AVL;

AVL *avl_create();

void avl_insert(AVL *avl, int value);

void avl_erase(AVL *avl, int value);

int avl_at(AVL *avl, int index);

int avl_size(AVL *avl);

void avl_destroy(AVL* avl);

#endif // !AVL_H
