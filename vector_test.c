#include "vector.h"
#include <stdio.h>
#include <assert.h>

// Test function to validate vector operations
void test_vector() {
    // Create a new vector
    Vector *v = vector_create();
    
    // Test initial length
    assert(vector_size(v) == 0);

    // Test appending elements
    vector_push_back(v, 10);
    vector_push_back(v, 20);
    vector_push_back(v, 30);

    // Check if values are added correctly and length is updated
    assert(vector_at(v, 0) == 10);
    assert(vector_at(v, 1) == 20);
    assert(vector_at(v, 2) == 30);
    assert(vector_size(v) == 3);
    printf("Append, access, and len test passed!\n");

    // Test popping elements and check length again
    assert(vector_pop_back(v) == 30);
    assert(vector_size(v) == 2);
    printf("Pop and size test passed!\n");

    // Cleanup
    vector_destroy(v);
    printf("Vector delete test passed!\n");
}

void test_large_append() {
    Vector *v = vector_create();
    int N = 1000000;  // 1 million elements

    for (int i = 0; i < N; i++) {
        vector_push_back(v, i);
    }

    // Ensure all elements are in the correct position
    for (int i = 0; i < N; i++) {
        assert(vector_at(v, i) == i);
    }

    assert(vector_size(v) == N);  // Ensure size is correct
    printf("Large append test passed!\n");

    vector_destroy(v);
}

int main() {
    // Run the test function
    test_vector();
    test_large_append();
    printf("All tests passed!\n");
    return 0;
}
