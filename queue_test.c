#include <assert.h>
#include <stdio.h>
#include "queue.h"

void test_queue_create_and_delete() {
    Queue* q = queue_create();
    assert(q != NULL);
    assert(queue_empty(q) == true);
    assert(queue_size(q) == 0);
    queue_delete(q);
    printf("test_queue_create_and_delete passed\n");
}

void test_queue_push_and_pop() {
    Queue* q = queue_create();
    queue_push(q, 1);
    queue_push(q, 2);
    queue_push(q, 3);

    assert(queue_size(q) == 3);
    assert(queue_front(q) == 1);
    assert(queue_pop(q) == 1);
    assert(queue_front(q) == 2);
    assert(queue_pop(q) == 2);
    assert(queue_front(q) == 3);
    assert(queue_pop(q) == 3);
    assert(queue_empty(q) == true);
    
    queue_delete(q);
    printf("test_queue_push_and_pop passed\n");
}

void test_queue_push_beyond_capacity() {
    Queue* q = queue_create();

    for (int i = 0; i < 10; ++i) {
        queue_push(q, i);
    }
    
    assert(queue_size(q) == 10);
    for (int i = 0; i < 10; ++i) {
        assert(queue_front(q) == i);
        assert(queue_pop(q) == i);
    }
    assert(queue_empty(q) == true);

    queue_delete(q);
    printf("test_queue_push_beyond_capacity passed\n");
}

void test_queue_shift() {
    Queue* q = queue_create();
    
    for (int i = 0; i < 5; ++i) {
        queue_push(q, i);
    }
    for (int i = 0; i < 3; ++i) {
        queue_pop(q);
    }

    queue_push(q, 10);
    queue_push(q, 11);
    
    assert(queue_size(q) == 4);
    assert(queue_front(q) == 3);
    assert(queue_pop(q) == 3);
    assert(queue_front(q) == 4);
    assert(queue_pop(q) == 4);
    assert(queue_front(q) == 10);
    assert(queue_pop(q) == 10);
    assert(queue_front(q) == 11);
    assert(queue_pop(q) == 11);
    assert(queue_empty(q) == true);

    queue_delete(q);
    printf("test_queue_shift passed\n");
}

int main() {
    test_queue_create_and_delete();
    test_queue_push_and_pop();
    test_queue_push_beyond_capacity();
    test_queue_shift();

    printf("All tests passed!\n");
    return 0;
}
