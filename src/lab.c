#include "lab.h"
#include <stdlib.h>
#include <sys/time.h>

static void insertion_sort(int A[], int p, int r) {
    int j;
    for (j = p + 1; j <= r; j++) {
        int key = A[j];
        int i = j - 1;
        while ((i > p - 1) && (A[i] > key)) {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;
    }
}

void mergesort_s(int A[], int p, int r) {
    if (r - p + 1 <= INSERTION_SORT_THRESHOLD) {
        insertion_sort(A, p, r);
    } else {
        int q = (p + r) / 2;
        mergesort_s(A, p, q);
        mergesort_s(A, q + 1, r);
        merge_s(A, p, q, r);
    }
}

void merge_s(int A[], int p, int q, int r) {
    int *B = (int *)malloc(sizeof(int) * (r - p + 1));
    int i = p, j = q + 1, k = 0;

    while ((i <= q) && (j <= r)) {
        if (A[i] < A[j]) {
            B[k++] = A[i++];
        } else {
            B[k++] = A[j++];
        }
    }

    while (i <= q) B[k++] = A[i++];
    while (j <= r) B[k++] = A[j++];

    for (k = 0, i = p; i <= r; i++, k++) {
        A[i] = B[k];
    }

    free(B);
}

void *parallel_mergesort(void *args) {
    struct parallel_args *p_args = (struct parallel_args *)args;
    mergesort_s(p_args->A, p_args->start, p_args->end);
    return NULL;
}

void mergesort_mt(int *A, int n, int num_threads) {
    // Adjust the number of threads if the array is too small
    if (num_threads > n) {
        num_threads = n;
    }

    pthread_t threads[num_threads];
    struct parallel_args thread_args[num_threads];
    int chunk_size = n / num_threads;
    int remainder = n % num_threads;

    for (int i = 0; i < num_threads; i++) {
        thread_args[i].A = A;
        thread_args[i].start = i * chunk_size + (i < remainder ? i : remainder);
        thread_args[i].end = thread_args[i].start + chunk_size - 1 + (i < remainder ? 1 : 0);
        
        // Debugging print statement for start and end values
        //printf("Thread %d: start=%d, end=%d\n", i, thread_args[i].start, thread_args[i].end);
        
        pthread_create(&threads[i], NULL, parallel_mergesort, &thread_args[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merging phase
    for (int size = chunk_size; size < n; size *= 2) {
        for (int i = 0; i < n; i += 2 * size) {
            int mid = i + size - 1;
            int end = (i + 2 * size - 1 < n) ? (i + 2 * size - 1) : (n - 1);
            if (mid < end) {
                merge_s(A, i, mid, end);
            }
        }
    }
}


double getMilliSeconds() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return (double)now.tv_sec * 1000.0 + (double)now.tv_usec / 1000.0;
}
