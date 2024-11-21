#include <stdio.h>

#define N 12

int binary_search(int arr[], int value, int l, int r) { 
    if(l == r) {
        return l;
    }

    int m = (l+r)/2;

    if(arr[m] >= value) {
        return binary_search(arr, value, l, m);
    }
    
    return binary_search(arr, value, m + 1, r);
}

int main() {
    int a[N] = {1, 12, 16, 22, 22, 23, 32, 44, 134, 142, 414, 414}; 
    int search_value = 22;
    int index = binary_search(a, search_value, 0, N - 1);

    printf("index of %d is %d\n", search_value, index);
}