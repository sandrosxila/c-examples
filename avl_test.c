#include "avl.h"
#include <assert.h>
#include <stdio.h>

// Helper to print test status
void print_test(const char* test_name, int status) {
    if (status) {
        printf("[PASS] %s\n", test_name);
    } else {
        printf("[FAIL] %s\n", test_name);
    }
}

// Test insertion and size validation
void test_insert_and_size() {
    AVL *avl = avl_create();
    avl_insert(avl, 10);
    avl_insert(avl, 20);
    avl_insert(avl, 30);
    avl_insert(avl, 5);
    avl_insert(avl, 15);

    assert(avl_size(avl) == 5); // Size must be 5 after 5 insertions
    print_test("Insert and Size Test", avl_size(avl) == 5);

    avl_destroy(avl);
}

// Test balance property (simple)
void test_balance_property_simple() {
    AVL *avl = avl_create();
    avl_insert(avl, 10);
    avl_insert(avl, 20);
    avl_insert(avl, 30); // Right-right rotation

    assert(avl_at(avl, 1) == 20); // Root in sorted order should be 20
    assert(avl_at(avl, 0) == 10); // Left child
    assert(avl_at(avl, 2) == 30); // Right child

    avl_destroy(avl);
    print_test("Balance Property Simple Test", 1);
}

// Test balance property (complex - left-right case)
void test_balance_property_complex() {
    AVL *avl = avl_create();
    avl_insert(avl, 10);
    avl_insert(avl, 30);
    avl_insert(avl, 20); // Left-right rotation

    assert(avl_at(avl, 1) == 20); // Root in sorted order should be 20
    assert(avl_at(avl, 0) == 10); // Left child
    assert(avl_at(avl, 2) == 30); // Right child

    avl_destroy(avl);
    print_test("Balance Property Complex Test", 1);
}

// Test deletion of nodes
void test_deletion() {
    AVL *avl = avl_create();
    avl_insert(avl, 10);
    avl_insert(avl, 20);
    avl_insert(avl, 30);
    avl_insert(avl, 5);

    avl_erase(avl, 20); // Delete node with no children
    assert(avl_size(avl) == 3);
    assert(avl_at(avl, 0) == 5);
    assert(avl_at(avl, 1) == 10);
    assert(avl_at(avl, 2) == 30);

    avl_erase(avl, 10); // Delete node with one child
    assert(avl_size(avl) == 2);
    assert(avl_at(avl, 0) == 5);
    assert(avl_at(avl, 1) == 30);

    avl_destroy(avl);
    print_test("Deletion Test", 1);
}

// Test deletion of root node
void test_deletion_of_root() {
    AVL *avl = avl_create();
    avl_insert(avl, 10);
    avl_insert(avl, 20);
    avl_insert(avl, 5);

    avl_erase(avl, 10); // Delete root
    assert(avl_size(avl) == 2);
    assert(avl_at(avl, 0) == 5);  // Ensure sorted order remains valid
    assert(avl_at(avl, 1) == 20);

    avl_destroy(avl);
    print_test("Deletion of Root Test", 1);
}

// Test index-based access
void test_index_access() {
    AVL *avl = avl_create();
    avl_insert(avl, 10);
    avl_insert(avl, 20);
    avl_insert(avl, 5);
    avl_insert(avl, 30);

    assert(avl_at(avl, 0) == 5);
    assert(avl_at(avl, 1) == 10);
    assert(avl_at(avl, 2) == 20);
    assert(avl_at(avl, 3) == 30);

    avl_destroy(avl);
    print_test("Index Access Test", 1);
}

// Run all tests
int main() {
    printf("Running AVL Tree Tests...\n");

    test_insert_and_size();
    test_balance_property_simple();
    test_balance_property_complex();
    test_deletion();
    test_deletion_of_root();
    test_index_access();

    printf("All tests completed.\n");
    return 0;
}
