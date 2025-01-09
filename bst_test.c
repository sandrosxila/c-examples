#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "bst.h"

void test_bst_create() {
    BST *bst = bst_create();
    assert(bst != NULL);
    bst_destroy(bst);
    printf("test_bst_create passed\n");
}

void test_bst_insert() {
    BST *bst = bst_create();
    bst_insert(bst, 10);
    bst_insert(bst, 5);
    bst_insert(bst, 15);
    assert(bst_at(bst, 0) == 5);
    assert(bst_at(bst, 1) == 10);
    assert(bst_at(bst, 2) == 15);
    bst_destroy(bst);
    printf("test_bst_insert passed\n");
}

void test_bst_at() {
    BST *bst = bst_create();
    bst_insert(bst, 20);
    bst_insert(bst, 10);
    bst_insert(bst, 30);
    bst_insert(bst, 25);
    bst_insert(bst, 35);

    assert(bst_at(bst, 0) == 10);
    assert(bst_at(bst, 1) == 20);
    assert(bst_at(bst, 2) == 25);
    assert(bst_at(bst, 3) == 30);
    assert(bst_at(bst, 4) == 35);

    bst_destroy(bst);
    printf("test_bst_at passed\n");
}

void test_bst_erase() {
    BST *bst = bst_create();
    bst_insert(bst, 20);
    bst_insert(bst, 10);
    bst_insert(bst, 30);
    bst_insert(bst, 25);
    bst_insert(bst, 35);

    bst_erase(bst, 10); // Leaf node
    assert(bst_at(bst, 0) == 20);

    bst_erase(bst, 30); // Node with one child
    assert(bst_at(bst, 1) == 25);

    bst_erase(bst, 20); // Node with two children
    assert(bst_at(bst, 0) == 25);
    assert(bst_at(bst, 1) == 35);

    bst_destroy(bst);
    printf("test_bst_erase passed\n");
}

void test_bst_size() {
    BST *bst = bst_create();
    bst_insert(bst, 20);
    bst_insert(bst, 10);
    bst_insert(bst, 30);
    bst_insert(bst, 25);
    bst_insert(bst, 35);

    bst_erase(bst, 10);
    bst_erase(bst, 30);
    bst_erase(bst, 20);

    assert(bst_size(bst) == 2);

    bst_destroy(bst);
    printf("test_bst_size passed\n");
}

void test_bst_balance() {
    BST *bst = bst_create();
    bst_insert(bst, 10);
    bst_insert(bst, 20);
    bst_insert(bst, 30);
    bst_insert(bst, 40);
    bst_insert(bst, 50);

    bst_balance(bst);
    assert(bst_at(bst, 0) == 10);
    assert(bst_at(bst, 1) == 20);
    assert(bst_at(bst, 2) == 30);
    assert(bst_at(bst, 3) == 40);
    assert(bst_at(bst, 4) == 50);

    bst_destroy(bst);
    printf("test_bst_balance passed\n");
}

void test_bst_destroy() {
    BST *bst = bst_create();
    bst_insert(bst, 10);
    bst_insert(bst, 20);
    bst_insert(bst, 30);
    bst_destroy(bst);
    printf("test_bst_destroy passed\n");
}

int main() {
    test_bst_create();
    test_bst_insert();
    test_bst_at();
    test_bst_erase();
    test_bst_balance();
    test_bst_destroy();
    printf("All tests passed!\n");
    return 0;
}
