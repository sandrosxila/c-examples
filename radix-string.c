#include <stdio.h>
#include <string.h>

#define N 12
#define DIGITS 10

char *aux[DIGITS][N];
int size[DIGITS] = {0};

void radix_sort(char *arr[], int l, int r) { 
    int max_len = 0;

    for(int i = l; i <= r; i++) {
        int len = strlen(arr[i]);
        if(max_len < len) 
            max_len = len;
    }

    for(int i = 1; i <= max_len; i++) {
        for(int j = l; j <= r; j++) {
            int len = strlen(arr[j]);
            int digit = len - i >= 0 ? (int)(arr[j][len - i] - '0') : 0;
            aux[digit][size[digit]++] = arr[j];
        }

        for(int digit = 0, pos = l; digit < DIGITS; digit++) {
            for(int j = 0; j < size[digit]; j++) {
                arr[pos++] = aux[digit][j];
                aux[digit][j] = NULL;
            }

            size[digit] = 0;
        }
    }
}

int main() {
    char *a[N] = {"10", "3221", "5622", "1", "9682", "5622", "4793", "3221", "9425", "577", "7", "2038"};

    radix_sort(a, 0, N - 1);

    for(int i = 0; i < N; i++) {
        printf("%s ", a[i]);
    }
    printf("\n");
}