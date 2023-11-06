#include "insert.h"

#include <stdio.h>
#include <stdlib.h>

void insertion_sort(Stats *stats, int *arr, int length) {
    int k, temp, j;

    for (k = 1; k < length; k++) {
        j = k;
        temp = move(stats, arr[k]);

        while (j >= 1 && cmp(stats, temp, arr[j - 1]) < 0) {
            arr[j] = move(stats, arr[j - 1]);
            j--;
        }
        arr[j] = move(stats, temp);
    }
}
