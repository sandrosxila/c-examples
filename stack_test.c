#include "stack.h"
#include <stdio.h>
#include <assert.h>

// Test function to validate vector operations
void test_stack() {
    // Create a new vector
    Stack *s = stack_create();
    
    // Test initial size
    assert(stack_size(s) == 0);

    // Test appending elements
    stack_push(s, 10);
    stack_push(s, 20);
    stack_push(s, 30);

    // Check if values are added correctly and size is updated
    assert(stack_top(s) == 30);
    assert(stack_size(s) == 3);
    printf("Push, top, and size test passed!\n");

    // Test popping elements and check size again
    assert(stack_pop(s) == 30);
    assert(stack_size(s) == 2);
    printf("Pop and size test passed!\n");

    // Cleanup
    stack_destroy(s);
    printf("Stack delete test passed!\n");
}

int main() {
    // Run the test function
    test_stack();
    printf("All tests passed!\n");
    return 0;
}
