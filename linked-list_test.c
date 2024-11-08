#include "linked-list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_linked_list() {
    int elements[] = { 1, 20, 14, 26, 17, 79, 89};

    List *list = list_create();

    for(int i = 0; i < sizeof(elements) / sizeof(int); i++) {
        list_push(list, elements[i]);
    }

    printf("push test passed!\n");

    for(int i = 0; i < sizeof(elements) / sizeof(int); i++) {
        assert(list_at(list, i)->value == elements[i]);
    }

    printf("access test passed!\n");

    list_erase(list, 1);
    list_erase(list, 17);
    list_erase(list, 77);
    list_erase(list, 89);

    int expected_elements[] = { 20, 14, 26, 79};

    for(int i = 0; i < sizeof(expected_elements) / sizeof(int); i++) {
        assert(list_at(list, i)->value == expected_elements[i]);
    }

    printf("deletion test passed!\n");

    assert(list_size(list) == 4);

    printf("length test passed!\n");

    list_clear(list);
    assert(list_at(list, 0) == NULL);
    assert(list_size(list) == 0);

    printf("clearing test passed!\n");

    free(list);
}

int main()
{
    test_linked_list();
    printf("All tests passed!\n");

    return 0;
}