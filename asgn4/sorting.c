#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int opt;
    int seed = 13371453;
    int p = 100;
    int n = 100;
    Set tracker = set_empty();
    unsigned int bit_mask = 0x3FFFFFFF;

    while ((opt = getopt(argc, argv, "Hahbsqin:p:r:")) != -1) {
        switch (opt) {
        case 'H':
            printf("SYNOPSIS\n"
                   "   A collection of comparison-based sorting algorithms.\n\n"
                   "USAGE\n"
                   "   ./sorting [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\n"
                   "OPTIONS\n"
                   "-H              Display program help and usage.\n"
                   "-a              Enable all sorts.\n"
                   "-h              Enable Heap Sort.\n"
                   "-b              Enable Batcher Sort.\n"
                   "-s              Enable Shell Sort.\n"
                   "-q              Enable Quick Sort.\n"
                   "-i              Enable Insertion Sort.\n"
                   "-n length       Specify number of array elements (default: 100).\n"
                   "-p elements     Specify number of elements to print (default: 100).\n"
                   "-r seed         Specify random seed (default: 13371453).\n");
            return 0;
        case 'a': tracker = set_universal(); break;
        case 'h': tracker = set_insert(tracker, 0); break;
        case 'b': tracker = set_insert(tracker, 1); break;
        case 's': tracker = set_insert(tracker, 2); break;
        case 'q': tracker = set_insert(tracker, 3); break;
        case 'i': tracker = set_insert(tracker, 4); break;
        case 'n': n = atoi(optarg); break;
        case 'p': p = atoi(optarg); break;
        case 'r': seed = atoi(optarg); break;
       	case '?': printf("./sorting: invalid option -- '%c'\n", opt);
            printf("SYNOPSIS\n"
                   "   A collection of comparison-based sorting algorithms.\n\n"
                   "USAGE\n"
                   "   ./sorting [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\n"
                   "OPTIONS\n"
                   "-H              Display program help and usage.\n"
                   "-a              Enable all sorts.\n"
                   "-h              Enable Heap Sort.\n"
                   "-b              Enable Batcher Sort.\n"
                   "-s              Enable Shell Sort.\n"
                   "-q              Enable Quick Sort.\n"
                   "-i              Enable Insertion Sort.\n"
                   "-n length       Specify number of array elements (default: 100).\n"
                   "-p elements     Specify number of elements to print (default: 100).\n"
                   "-r seed         Specify random seed (default: 13371453).\n");
            return 0;
        }
    }

    Stats stats;

    if (set_member(tracker, 4)) {
        srandom(seed);
        reset(&stats);

        int *A;
        A = (int *) calloc(n, sizeof(int));
        for (int i = 0; i < n; i++) {
            A[i] = random() & bit_mask;
        }

        insertion_sort(&stats, A, n);
        print_stats(&stats, "Insertion Sort", n);
	
	int k = 0;
	while (k < p && k < n){
		for (int j = 0; j < 5; j++){
			printf("%13d", A[k]);
			k++;
			if (k >= p || k >= n){
                                printf("%c", '\n');
				break;
			}
			if (j == 4){
				printf("%c", '\n');
			}
		}
	}

        free(A);
    }

    if (set_member(tracker, 0)) {
        srandom(seed);
        reset(&stats);

        int *A;
        A = (int *) calloc(n, sizeof(int));
        for (int i = 0; i < n; i++) {
            A[i] = random() & bit_mask;
        }

        heap_sort(&stats, A, n);
        print_stats(&stats, "Heap Sort", n);
        
	int k = 0;
        while (k < p && k < n){
                for (int j = 0; j < 5; j++){
                        printf("%13d", A[k]);
                        k++;
                        if (k >= p || k >= n){
                                printf("%c", '\n');
                                break;
                        }
                        if (j == 4){
                                printf("%c", '\n');
                        }
                }
        }

        free(A);
    }

    if (set_member(tracker, 2)) {
        srandom(seed);
        reset(&stats);

        int *A;
        A = (int *) calloc(n, sizeof(int));
        for (int i = 0; i < n; i++) {
            A[i] = random() & bit_mask;
        }

        shell_sort(&stats, A, n);
        print_stats(&stats, "Shell Sort", n);

        int k = 0;
        while (k < p && k < n){
                for (int j = 0; j < 5; j++){
                        printf("%13d", A[k]);
                        k++;
                        if (k >= p || k >= n){
                                printf("%c", '\n');
                                break;
                        }
                        if (j == 4){
                                printf("%c", '\n');
                        }
                }
        }

        free(A);
    }

    if (set_member(tracker, 3)) {
        srandom(seed);
        reset(&stats);

        int *A;
        A = (int *) calloc(n, sizeof(int));
        for (int i = 0; i < n; i++) {
            A[i] = random() & bit_mask;
        }

        quick_sort(&stats, A, n);
        print_stats(&stats, "Quick Sort", n);

        int k = 0;
        while (k < p && k < n){
                for (int j = 0; j < 5; j++){
                        printf("%13d", A[k]);
                        k++;
                        if (k >= p || k >= n){
                                printf("%c", '\n');
                                break;
                        }
                        if (j == 4){
                                printf("%c", '\n');
                        }
                }
        }

        free(A);
    }

    if (set_member(tracker, 1)) {
        srandom(seed);
        reset(&stats);

        int *A;
        A = (int *) calloc(n, sizeof(int));
        for (int i = 0; i < n; i++) {
            A[i] = random() & bit_mask;
        }

        batcher_sort(&stats, A, n);
        print_stats(&stats, "Batcher Sort", n);

        int k = 0;
        while (k < p && k < n){
                for (int j = 0; j < 5; j++){
                        printf("%13d", A[k]);
                        k++;
                        if (k >= p || k >= n){
                                printf("%c", '\n');
                                break;
                        }
                        if (j == 4){
                                printf("%c", '\n');
                        }
                }
        }

        free(A);
    }

    return 0;
}
