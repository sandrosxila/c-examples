#include <stdio.h>

#define N 12
#define DIGITS 10

int aux[DIGITS][N];
int size[DIGITS] = {0};

void radix_sort(int arr[], int l, int r) { 
    int max_len = 0;
    for(int i = l; i <= r; i++) {
        int len = 0;
        for(int num = arr[i]; num > 0; num /= 10) len++;

        max_len = max_len < len ? len : max_len;
    }

    int factor = 1;
    for(int i = 1; i <= max_len; i++) {
        for(int j = l; j <= r; j++) {
            int digit = (arr[j] / factor) % 10;
            aux[digit][size[digit]++] = arr[j];
        }
        for(int digit = 0, pos = l; digit < DIGITS; digit++) {
            for(int j = 0; j < size[digit]; j++) {
                arr[pos++] = aux[digit][j];
                aux[digit][j] = 0;
            }

            size[digit] = 0;
        }

        factor *= 10;
    }
}

int main() {
    int a[N] = {22, 314, 1, 32, 44, 12, 42, 4014, 2553, 414, 134, 142};

    radix_sort(a, 0, N - 1);

    for(int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}