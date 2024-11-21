#include <stdio.h>

#define N 12

int aux[N];

void merge(int arr[], int l, int r) {
    int m = (l+r)/2;
    for(int i = l, j = m + 1, aux_idx = l; aux_idx <= r; aux_idx++){
        if (i > m || (j <= r && arr[j] < arr[i])) {
            aux[aux_idx] = arr[j++];
        } else {
            aux[aux_idx] = arr[i++];
        }
    }

    for(int i = l; i <= r; i++) {
        arr[i] = aux[i];
    }
}

void merge_sort(int arr[], int l, int r) { 
    if(l == r) {
        return;
    }

    int m = (l+r)/2;

    merge_sort(arr, l, m);
    merge_sort(arr, m + 1, r);

    merge(arr, l, r);
}

int main() {
    int a[N] = {22, 314, 1, 32, 44, 12, 42, 414, 23, 414, 134, 142};

    merge_sort(a, 0, N - 1);

    for(int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}