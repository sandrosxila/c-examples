#include <stdio.h>

#define N 12

void swap(int *a, int *b) {
    int temp = *a; *a = *b; *b = temp;
}

void heap_erase(int arr[], int l, int r) {
    if(arr[l] > arr[r]) // Replace the root if necessary
        swap(&arr[l], &arr[r]);

    for(int i = 0; i + l < (r - 1) / 2;) { 
        // Compare the new root with its children 
        int left_i = 2 * i + 1, right_i = 2 * i + 2;
        int next_i = 
            arr[left_i + l] > arr[right_i + l] ? left_i : right_i;
        
        // If the heap property is broken, swap the root with the larger child 
        if(arr[next_i + l] > arr[i + l]){ 
            swap(&arr[next_i + l], &arr[i + l]);
        }
        else break;

        i = next_i;
    }
}

void heap_insert(int arr[], int l, int r) {
    for(int i = r - l; i > 0; i = (i - 1) / 2) {
        // Compare the new number with its parent
        if(arr[i + l] > arr[(i - 1) / 2 + l]) { 
            // If the heap property is broken, swap the new number with its parent
            swap(&arr[i + l], &arr[(i - 1) / 2 + l]);
        }
        else break;
    }
}

void heap_sort(int arr[], int l, int r) { 
    for(int i = l + 1; i <= r; i++)
        heap_insert(arr, l, i);

    for(int i = r; i > l; i--)
        heap_erase(arr, l, i);
}

int main() {
    int a[N] = {22, 314, 1, 32, 414, 42, 42, 414, 134, 414, 134, 142};

    heap_sort(a, 0, N - 1);

    for(int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}