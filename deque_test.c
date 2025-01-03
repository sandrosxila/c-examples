#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "deque.h"

void test_empty_deque() {
    Deque* d = deque_create();
    assert(deque_empty(d) == true); // Deque should be empty initially
    assert(deque_size(d) == 0);     // Size should be 0 initially
    deque_destroy(d);
    printf("test_empty_deque passed\n");
}

void test_push_front_and_back() {
    Deque* d = deque_create();

    deque_push_back(d, 1);
    assert(deque_size(d) == 1);
    assert(deque_front(d) == 1);
    assert(deque_back(d) == 1);

    deque_push_front(d, 2);
    assert(deque_size(d) == 2);
    assert(deque_front(d) == 2);
    assert(deque_back(d) == 1);

    deque_push_back(d, 3);
    assert(deque_size(d) == 3);
    assert(deque_front(d) == 2);
    assert(deque_back(d) == 3);

    deque_destroy(d);
    printf("test_push_front_and_back passed\n");
}

void test_pop_front_and_back() {
    Deque* d = deque_create();

    deque_push_back(d, 1);
    deque_push_back(d, 2);
    deque_push_back(d, 3);

    int val = deque_pop_front(d);
    assert(val == 1); // First element popped from front
    assert(deque_size(d) == 2);
    assert(deque_front(d) == 2);
    assert(deque_back(d) == 3);

    val = deque_pop_back(d);
    assert(val == 3); // Last element popped from back
    assert(deque_size(d) == 1);
    assert(deque_front(d) == 2);
    assert(deque_back(d) == 2);

    val = deque_pop_front(d);
    assert(val == 2); // Last element popped from front
    assert(deque_size(d) == 0);
    assert(deque_empty(d) == true); // Deque should be empty now

    deque_destroy(d);
    printf("test_pop_front_and_back passed\n");
}

void test_push_and_pop_edge_cases() {
    Deque* d = deque_create();

    // Pop from an empty deque (should crash program)
    // Uncomment the following to see the crash behavior
    // deque_pop_back(d); // Should cause exit due to empty deque
    // deque_pop_front(d); // Should cause exit due to empty deque

    // Test pushing and popping when there is only one element
    deque_push_back(d, 10);
    assert(deque_size(d) == 1);
    assert(deque_front(d) == 10);
    assert(deque_back(d) == 10);

    int val = deque_pop_back(d);
    assert(val == 10);
    assert(deque_size(d) == 0);
    assert(deque_empty(d) == true);

    deque_destroy(d);
    printf("test_push_and_pop_edge_cases passed\n");
}

void test_memory_leaks_and_deletion() {
    // Allocate and destroy a deque multiple times to ensure no memory leaks
    for (int i = 0; i < 1000; ++i) {
        Deque* d = deque_create();
        for (int j = 0; j < 100; ++j) {
            deque_push_back(d, j);
        }
        for (int j = 0; j < 100; ++j) {
            deque_pop_front(d);
        }
        deque_destroy(d);
    }
    printf("test_memory_leaks_and_deletion passed\n");
}

void test_large_deque_operations() {
    Deque* d = deque_create();

    // Test pushing large numbers of elements to the back and front
    for (int i = 0; i < 100000; ++i) {
        deque_push_back(d, i);
    }
    assert(deque_size(d) == 100000);
    
    for (int i = 0; i < 50000; ++i) {
        deque_pop_front(d);
    }
    assert(deque_size(d) == 50000);
    
    for (int i = 0; i < 50000; ++i) {
        deque_pop_back(d);
    }
    assert(deque_size(d) == 0);
    assert(deque_empty(d) == true);

    deque_destroy(d);
    printf("test_large_deque_operations passed\n");
}

int main() {
    test_empty_deque();
    test_push_front_and_back();
    test_pop_front_and_back();
    test_push_and_pop_edge_cases();
    test_memory_leaks_and_deletion();
    test_large_deque_operations();

    printf("All tests passed!\n");
    return 0;
}
