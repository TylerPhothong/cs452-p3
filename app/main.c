#include <stdio.h>
#include <stdlib.h>
#include "lab.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("usage: %s <array_size> <num_threads>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    int num_threads = atoi(argv[2]);

    int *A = malloc(sizeof(int) * size);
    srandom(1);
    for (int i = 0; i < size; i++) {
        A[i] = random() % 100000;
    }

    double start = getMilliSeconds();
    mergesort_mt(A, size, num_threads);
    double end = getMilliSeconds();

    printf("Time taken: %f ms with %d threads\n", end - start, num_threads);

    free(A);
    return 0;
}
