#ifndef LAB_H
#define LAB_H

#include <pthread.h>

#define INSERTION_SORT_THRESHOLD 2
#define MAX_THREADS 32

#ifdef __cplusplus
extern "C" {
#endif

void mergesort_s(int *A, int p, int r);
void merge_s(int A[], int p, int q, int r);
void mergesort_mt(int *A, int n, int num_thread);
double getMilliSeconds();
void *parallel_mergesort(void *args);

struct parallel_args {
    int *A;
    int start;
    int end;
    pthread_t tid;
};

#ifdef __cplusplus
}
#endif

#endif
