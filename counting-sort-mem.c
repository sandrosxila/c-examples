#include <stdio.h>
#include <string.h>
#include <limits.h>

#define N 12

void counting_sort(int arr[], int l, int r) { 
    int max_num = INT_MIN;
    for(int i = l; i <= r; i++)
        max_num = max_num < arr[i] ? arr[i] : max_num;

    const int M = max_num + 1, LEN = r - l + 1;

    int count[M];
    memset(count, 0, sizeof(count)); // fill array with 0

    for(int i = l; i <= r; i++)
        count[arr[i]]++;

    for(int i = 1; i < M; i++)
        count[i] += count[i - 1];

    int aux[LEN];
    memcpy(aux, arr + l, sizeof(aux)); // copy arr[l..r] to aux

    for(int i = r; i >= l; i--) {
        int elem = aux[i - l];
        int pos = count[elem] - 1 + l;
        arr[pos] = elem;
        count[elem]--;
    }
}

int main() {
    int a[N] = {22, 314, 1, 32, 414, 42, 42, 414, 134, 414, 134, 142};

    counting_sort(a, 0, N - 1);

    for(int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}