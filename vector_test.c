#include "vector.h"
#include <stdio.h>
#include <assert.h>

// Test function to validate vector operations
void test_vector() {
    // Create a new vector
    Vector *v = new_vector();
    
    // Test initial length
    assert(len(v) == 0);

    // Test appending elements
    append(v, 10);
    append(v, 20);
    append(v, 30);

    // Check if values are added correctly and length is updated
    assert(get(v, 0) == 10);
    assert(get(v, 1) == 20);
    assert(get(v, 2) == 30);
    assert(len(v) == 3);
    printf("Append, access, and len test passed!\n");

    // Test popping elements and check length again
    assert(pop_back(v) == 30);
    assert(len(v) == 2);
    printf("Pop and size test passed!\n");

    // Cleanup
    delete_vector(v);
    printf("Vector delete test passed!\n");
}

void test_large_append() {
    Vector *v = new_vector();
    int N = 1000000;  // 1 million elements

    for (int i = 0; i < N; i++) {
        append(v, i);
    }

    // Ensure all elements are in the correct position
    for (int i = 0; i < N; i++) {
        assert(get(v, i) == i);
    }

    assert(len(v) == N);  // Ensure size is correct
    printf("Large append test passed!\n");

    delete_vector(v);
}

int main() {
    // Run the test function
    test_vector();
    test_large_append();
    printf("All tests passed!\n");
    return 0;
}
