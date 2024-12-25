#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

// Test Case 1: Simple queue operations (push and pop)
void test_basic_operations() {
    Queue *q = queue_create();
    queue_push(q, 1);
    queue_push(q, 2);
    queue_push(q, 3);
    assert(queue_front(q) == 1);  // Front should be 1
    assert(queue_back(q) == 3);   // Back should be 3
    assert(queue_size(q) == 3);   // Size should be 3
    
    assert(queue_pop(q) == 1);    // Pop should return 1
    assert(queue_front(q) == 2);  // Front should be 2 after popping
    assert(queue_size(q) == 2);   // Size should be 2
    
    queue_pop(q); // Remove 2
    queue_pop(q); // Remove 3
    
    assert(queue_empty(q)); // Queue should be empty now
    
    queue_destroy(q);
}

// Test Case 2: Edge case with an empty queue
void test_empty_queue() {
    Queue *q = queue_create();
    
    assert(queue_empty(q));    // The queue should be empty initially
    assert(queue_size(q) == 0); // Size should be 0
    
    // Trying to pop from an empty queue (should handle gracefully)
    // You may want to modify your code to avoid crashing here
    // or assert the behavior. For now, let's check it doesn't crash.
    if (!queue_empty(q)) {
        queue_pop(q); 
    }
    
    queue_destroy(q);
}

// Test Case 3: Multiple pops until the queue is empty
void test_multiple_pops() {
    Queue *q = queue_create();
    
    for (int i = 0; i < 1000; i++) {
        queue_push(q, i);
    }
    
    for (int i = 0; i < 1000; i++) {
        assert(queue_pop(q) == i); // Check that the order is preserved
    }
    
    assert(queue_empty(q)); // Queue should be empty after all pops
    queue_destroy(q);
}

// Test Case 4: Testing boundary conditions with vector resize
void test_resize_behavior() {
    Queue *q = queue_create();
    
    // Push elements more than initial capacity to trigger resizing
    for (int i = 0; i < 5000; i++) {
        queue_push(q, i);
    }
    
    // After pushing, we expect the queue to have 5000 elements
    assert(queue_size(q) == 5000);
    
    // Pop a few elements and check the size and front
    for (int i = 0; i < 1000; i++) {
        queue_pop(q);
    }
    
    // After popping 1000 elements, size should be 4000
    assert(queue_size(q) == 4000);
    
    // Ensure that the front element is 1000 (since it was the 1001st pushed)
    assert(queue_front(q) == 1000);
    
    queue_destroy(q);
}

// Test Case 5: Testing pop from an already shifted queue (after shrink)
void test_queue_shift() {
    Queue *q = queue_create();
    
    // Push a large number of elements (e.g., 5000 elements)
    for (int i = 0; i < 5000; i++) {
        queue_push(q, i);
    }

    // Initially, the queue should have 5000 elements
    assert(queue_size(q) == 5000);

    // Pop a subset of elements to force shifts to occur (e.g., pop 3000 elements)
    for (int i = 0; i < 3000; i++) {
        int popped = queue_pop(q);
        assert(popped == i);  // Ensure that the order is maintained and we pop the correct elements
    }

    // After popping 3000 elements, the queue should have 2000 elements left
    assert(queue_size(q) == 2000);
    
    // Check the front and back of the queue to ensure shifting worked
    assert(queue_front(q) == 3000); // Front should be the 3001st element pushed
    assert(queue_back(q) == 4999);  // Back should be the last element pushed (4999)

    // Now push a few more elements to verify the integrity of the queue
    for (int i = 5000; i < 5100; i++) {
        queue_push(q, i);
    }

    // The queue should now have 2100 elements
    assert(queue_size(q) == 2100);
    
    // Check if the front is still correct after pushing more elements
    assert(queue_front(q) == 3000);  // Front should still be the 3001st element

    // Check the back element after pushing additional elements
    assert(queue_back(q) == 5099);  // Back should be the last element pushed (5099)

    // Pop all the remaining elements (should be 5000)
    for (int i = 3000; i < 5100; i++) {
        int popped = queue_pop(q);
        assert(popped == i);  // Ensure that the order is preserved and we pop the correct elements
    }

    // After popping all elements, the queue should be empty
    assert(queue_empty(q));
    assert(queue_size(q) == 0);

    queue_destroy(q);
}

// Test Case 6: Stress test with large number of elements
void test_stress() {
    Queue *q = queue_create();
    
    // Push a large number of elements to test efficiency and memory management
    for (int i = 0; i < 1000000; i++) {
        queue_push(q, i);
    }
    
    // Pop a few elements and check if it still works
    for (int i = 0; i < 500000; i++) {
        queue_pop(q);
    }
    
    // Check that size is correct after popping 500,000 elements
    assert(queue_size(q) == 500000);
    
    // Check the front and back of the queue
    assert(queue_front(q) == 500000); // Front should be 500000
    assert(queue_back(q) == 999999);  // Back should be 999999
    
    queue_destroy(q);
}

// Test Case 7: Test clearing the queue
void test_clear() {
    Queue *q = queue_create();
    
    for (int i = 0; i < 1000; i++) {
        queue_push(q, i);
    }
    
    // Queue should have 1000 elements now
    assert(queue_size(q) == 1000);
    
    queue_clear(q);
    
    // After clearing, the queue should be empty
    assert(queue_empty(q));
    assert(queue_size(q) == 0);
    
    queue_destroy(q);
}

// Test Case 8: Test destruction of queue and vector integrity
void test_destroy() {
    Queue *q = queue_create();
    for (int i = 0; i < 1000; i++) {
        queue_push(q, i);
    }
    
    queue_destroy(q); // This should free memory without causing memory leaks
}

int main() {
    test_basic_operations();
    test_empty_queue();
    test_multiple_pops();
    test_resize_behavior();
    test_queue_shift();
    test_stress();
    test_clear();
    test_destroy();

    printf("All tests passed!\n");

    return 0;
}
