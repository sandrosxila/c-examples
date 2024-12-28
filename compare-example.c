#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 12

void swap(void *x, void *y, size_t elem_size)
{
    void *temp = malloc(elem_size);  // Allocate space for one element

    // Copy the value from x to temp
    memcpy(temp, x, elem_size);

    // Copy the value from y to x
    memcpy(x, y, elem_size);

    // Copy the value from temp to y
    memcpy(y, temp, elem_size);

    // Free the temporary memory
    free(temp);
}

int myCompare (const int *a, const int *b) {
    if(*a < *b){
        return -1;
    }
    if(*a == *b) {
        return 0;
    }

    return 1;
}

int yourCompare (const int *a, const int *b) {
    if(*a > *b){
        return -1;
    }
    if(*a == *b) {
        return 0;
    }

    return 1;
}

void mysort(int *arr, size_t n, size_t elem_size, int (*compare)(const void *, const void *)){
    for(int i = 1; i < n; i++) {
        for(int j = i; j > 0; j--) {
            if(compare(&arr[j], &arr[j - 1]) < 0) {
                swap(&arr[j], &arr[j  - 1], elem_size);
            }
        }
    }
}


int main()
{
    int a[N] = {22, 314, 1, 32, 44, 12, 42, 4014, 2553, 414, 134, 142};
    
    // mysort(a, N, sizeof(int), yourCompare);
    mysort(a, N, sizeof(int), myCompare);

    for(int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    
    printf("\n");
}
