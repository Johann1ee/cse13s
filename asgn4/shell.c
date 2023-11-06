#include "shell.h"

#include "gaps.h"

#include <stdio.h>
#include <stdlib.h>

void shell_sort(Stats *stats, int *A, int n) {
    int k, temp, j, gap;

    for (int i = 0; i < GAPS; i++) {
        gap = gaps[i];

        for (k = gap; k < n; k++) {
            j = k;
            temp = move(stats, A[k]);

            while (j >= gap && cmp(stats, temp, A[j - gap]) < 0) {
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = move(stats, temp);
        }
    }
}
