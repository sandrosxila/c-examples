#include "stack.h"
#include <stdio.h>
#include <assert.h>

// Test function to validate vector operations
void test_stack() {
    // Create a new vector
    Stack *s = new_stack();
    
    // Test initial size
    assert(size(s) == 0);

    // Test appending elements
    push(s, 10);
    push(s, 20);
    push(s, 30);

    // Check if values are added correctly and size is updated
    assert(top(s) == 30);
    assert(size(s) == 3);
    printf("Push, top, and size test passed!\n");

    // Test popping elements and check size again
    assert(pop(s) == 30);
    assert(size(s) == 2);
    printf("Pop and size test passed!\n");

    // Cleanup
    delete_stack(s);
    printf("Stack delete test passed!\n");
}

int main() {
    // Run the test function
    test_stack();
    printf("All tests passed!\n");
    return 0;
}
